<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * event tracer
 *
 * Copyright (C) 2008 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 *  - Added क्रमmat output of fields of the trace poपूर्णांक.
 *    This was based off of work by Tom Zanussi <tzanussi@gmail.com>.
 *
 */

#घोषणा pr_fmt(fmt) fmt

#समावेश <linux/workqueue.h>
#समावेश <linux/security.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/tracefs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/sort.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

#समावेश <trace/events/sched.h>
#समावेश <trace/syscall.h>

#समावेश <यंत्र/setup.h>

#समावेश "trace_output.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM "TRACE_SYSTEM"

DEFINE_MUTEX(event_mutex);

LIST_HEAD(ftrace_events);
अटल LIST_HEAD(ftrace_generic_fields);
अटल LIST_HEAD(ftrace_common_fields);
अटल bool eventdir_initialized;

#घोषणा GFP_TRACE (GFP_KERNEL | __GFP_ZERO)

अटल काष्ठा kmem_cache *field_cachep;
अटल काष्ठा kmem_cache *file_cachep;

अटल अंतरभूत पूर्णांक प्रणाली_refcount(काष्ठा event_subप्रणाली *प्रणाली)
अणु
	वापस प्रणाली->ref_count;
पूर्ण

अटल पूर्णांक प्रणाली_refcount_inc(काष्ठा event_subप्रणाली *प्रणाली)
अणु
	वापस प्रणाली->ref_count++;
पूर्ण

अटल पूर्णांक प्रणाली_refcount_dec(काष्ठा event_subप्रणाली *प्रणाली)
अणु
	वापस --प्रणाली->ref_count;
पूर्ण

/* Double loops, करो not use अवरोध, only जाओ's work */
#घोषणा करो_क्रम_each_event_file(tr, file)			\
	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु	\
		list_क्रम_each_entry(file, &tr->events, list)

#घोषणा करो_क्रम_each_event_file_safe(tr, file)			\
	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु	\
		काष्ठा trace_event_file *___n;				\
		list_क्रम_each_entry_safe(file, ___n, &tr->events, list)

#घोषणा जबतक_क्रम_each_event_file()		\
	पूर्ण

अटल काष्ठा ftrace_event_field *
__find_event_field(काष्ठा list_head *head, अक्षर *name)
अणु
	काष्ठा ftrace_event_field *field;

	list_क्रम_each_entry(field, head, link) अणु
		अगर (!म_भेद(field->name, name))
			वापस field;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा ftrace_event_field *
trace_find_event_field(काष्ठा trace_event_call *call, अक्षर *name)
अणु
	काष्ठा ftrace_event_field *field;
	काष्ठा list_head *head;

	head = trace_get_fields(call);
	field = __find_event_field(head, name);
	अगर (field)
		वापस field;

	field = __find_event_field(&ftrace_generic_fields, name);
	अगर (field)
		वापस field;

	वापस __find_event_field(&ftrace_common_fields, name);
पूर्ण

अटल पूर्णांक __trace_define_field(काष्ठा list_head *head, स्थिर अक्षर *type,
				स्थिर अक्षर *name, पूर्णांक offset, पूर्णांक size,
				पूर्णांक is_चिन्हित, पूर्णांक filter_type)
अणु
	काष्ठा ftrace_event_field *field;

	field = kmem_cache_alloc(field_cachep, GFP_TRACE);
	अगर (!field)
		वापस -ENOMEM;

	field->name = name;
	field->type = type;

	अगर (filter_type == FILTER_OTHER)
		field->filter_type = filter_assign_type(type);
	अन्यथा
		field->filter_type = filter_type;

	field->offset = offset;
	field->size = size;
	field->is_चिन्हित = is_चिन्हित;

	list_add(&field->link, head);

	वापस 0;
पूर्ण

पूर्णांक trace_define_field(काष्ठा trace_event_call *call, स्थिर अक्षर *type,
		       स्थिर अक्षर *name, पूर्णांक offset, पूर्णांक size, पूर्णांक is_चिन्हित,
		       पूर्णांक filter_type)
अणु
	काष्ठा list_head *head;

	अगर (WARN_ON(!call->class))
		वापस 0;

	head = trace_get_fields(call);
	वापस __trace_define_field(head, type, name, offset, size,
				    is_चिन्हित, filter_type);
पूर्ण
EXPORT_SYMBOL_GPL(trace_define_field);

#घोषणा __generic_field(type, item, filter_type)			\
	ret = __trace_define_field(&ftrace_generic_fields, #type,	\
				   #item, 0, 0, is_चिन्हित_type(type),	\
				   filter_type);			\
	अगर (ret)							\
		वापस ret;

#घोषणा __common_field(type, item)					\
	ret = __trace_define_field(&ftrace_common_fields, #type,	\
				   "common_" #item,			\
				   दुरत्व(typeof(ent), item),		\
				   माप(ent.item),			\
				   is_चिन्हित_type(type), FILTER_OTHER);	\
	अगर (ret)							\
		वापस ret;

अटल पूर्णांक trace_define_generic_fields(व्योम)
अणु
	पूर्णांक ret;

	__generic_field(पूर्णांक, CPU, FILTER_CPU);
	__generic_field(पूर्णांक, cpu, FILTER_CPU);
	__generic_field(अक्षर *, COMM, FILTER_COMM);
	__generic_field(अक्षर *, comm, FILTER_COMM);

	वापस ret;
पूर्ण

अटल पूर्णांक trace_define_common_fields(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा trace_entry ent;

	__common_field(अचिन्हित लघु, type);
	__common_field(अचिन्हित अक्षर, flags);
	__common_field(अचिन्हित अक्षर, preempt_count);
	__common_field(पूर्णांक, pid);

	वापस ret;
पूर्ण

अटल व्योम trace_destroy_fields(काष्ठा trace_event_call *call)
अणु
	काष्ठा ftrace_event_field *field, *next;
	काष्ठा list_head *head;

	head = trace_get_fields(call);
	list_क्रम_each_entry_safe(field, next, head, link) अणु
		list_del(&field->link);
		kmem_cache_मुक्त(field_cachep, field);
	पूर्ण
पूर्ण

/*
 * run-समय version of trace_event_get_offsets_<call>() that वापसs the last
 * accessible offset of trace fields excluding __dynamic_array bytes
 */
पूर्णांक trace_event_get_offsets(काष्ठा trace_event_call *call)
अणु
	काष्ठा ftrace_event_field *tail;
	काष्ठा list_head *head;

	head = trace_get_fields(call);
	/*
	 * head->next poपूर्णांकs to the last field with the largest offset,
	 * since it was added last by trace_define_field()
	 */
	tail = list_first_entry(head, काष्ठा ftrace_event_field, link);
	वापस tail->offset + tail->size;
पूर्ण

/*
 * Check अगर the referenced field is an array and वापस true,
 * as arrays are OK to dereference.
 */
अटल bool test_field(स्थिर अक्षर *fmt, काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_event_fields *field = call->class->fields_array;
	स्थिर अक्षर *array_descriptor;
	स्थिर अक्षर *p = fmt;
	पूर्णांक len;

	अगर (!(len = str_has_prefix(fmt, "REC->")))
		वापस false;
	fmt += len;
	क्रम (p = fmt; *p; p++) अणु
		अगर (!है_अक्षर_अंक(*p) && *p != '_')
			अवरोध;
	पूर्ण
	len = p - fmt;

	क्रम (; field->type; field++) अणु
		अगर (म_भेदन(field->name, fmt, len) ||
		    field->name[len])
			जारी;
		array_descriptor = म_अक्षर(field->type, '[');
		/* This is an array and is OK to dereference. */
		वापस array_descriptor != शून्य;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Examine the prपूर्णांक fmt of the event looking क्रम unsafe dereference
 * poपूर्णांकers using %p* that could be recorded in the trace event and
 * much later referenced after the poपूर्णांकer was मुक्तd. Dereferencing
 * poपूर्णांकers are OK, अगर it is dereferenced पूर्णांकo the event itself.
 */
अटल व्योम test_event_prपूर्णांकk(काष्ठा trace_event_call *call)
अणु
	u64 dereference_flags = 0;
	bool first = true;
	स्थिर अक्षर *fmt, *c, *r, *a;
	पूर्णांक parens = 0;
	अक्षर in_quote = 0;
	पूर्णांक start_arg = 0;
	पूर्णांक arg = 0;
	पूर्णांक i;

	fmt = call->prपूर्णांक_fmt;

	अगर (!fmt)
		वापस;

	क्रम (i = 0; fmt[i]; i++) अणु
		चयन (fmt[i]) अणु
		हाल '\\':
			i++;
			अगर (!fmt[i])
				वापस;
			जारी;
		हाल '"':
		हाल '\'':
			/*
			 * The prपूर्णांक fmt starts with a string that
			 * is processed first to find %p* usage,
			 * then after the first string, the prपूर्णांक fmt
			 * contains arguments that are used to check
			 * अगर the dereferenced %p* usage is safe.
			 */
			अगर (first) अणु
				अगर (fmt[i] == '\'')
					जारी;
				अगर (in_quote) अणु
					arg = 0;
					first = false;
					/*
					 * If there was no %p* uses
					 * the fmt is OK.
					 */
					अगर (!dereference_flags)
						वापस;
				पूर्ण
			पूर्ण
			अगर (in_quote) अणु
				अगर (in_quote == fmt[i])
					in_quote = 0;
			पूर्ण अन्यथा अणु
				in_quote = fmt[i];
			पूर्ण
			जारी;
		हाल '%':
			अगर (!first || !in_quote)
				जारी;
			i++;
			अगर (!fmt[i])
				वापस;
			चयन (fmt[i]) अणु
			हाल '%':
				जारी;
			हाल 'p':
				/* Find dereferencing fields */
				चयन (fmt[i + 1]) अणु
				हाल 'B': case 'R': case 'r':
				हाल 'b': case 'M': case 'm':
				हाल 'I': case 'i': case 'E':
				हाल 'U': case 'V': case 'N':
				हाल 'a': case 'd': case 'D':
				हाल 'g': case 't': case 'C':
				हाल 'O': case 'f':
					अगर (WARN_ONCE(arg == 63,
						      "Too many args for event: %s",
						      trace_event_name(call)))
						वापस;
					dereference_flags |= 1ULL << arg;
				पूर्ण
				अवरोध;
			शेष:
			अणु
				bool star = false;
				पूर्णांक j;

				/* Increment arg अगर %*s exists. */
				क्रम (j = 0; fmt[i + j]; j++) अणु
					अगर (है_अंक(fmt[i + j]) ||
					    fmt[i + j] == '.')
						जारी;
					अगर (fmt[i + j] == '*') अणु
						star = true;
						जारी;
					पूर्ण
					अगर ((fmt[i + j] == 's') && star)
						arg++;
					अवरोध;
				पूर्ण
				अवरोध;
			पूर्ण /* शेष */

			पूर्ण /* चयन */
			arg++;
			जारी;
		हाल '(':
			अगर (in_quote)
				जारी;
			parens++;
			जारी;
		हाल ')':
			अगर (in_quote)
				जारी;
			parens--;
			अगर (WARN_ONCE(parens < 0,
				      "Paren mismatch for event: %s\narg='%s'\n%*s",
				      trace_event_name(call),
				      fmt + start_arg,
				      (i - start_arg) + 5, "^"))
				वापस;
			जारी;
		हाल ',':
			अगर (in_quote || parens)
				जारी;
			i++;
			जबतक (है_खाली(fmt[i]))
				i++;
			start_arg = i;
			अगर (!(dereference_flags & (1ULL << arg)))
				जाओ next_arg;

			/* Find the REC-> in the argument */
			c = म_अक्षर(fmt + i, ',');
			r = म_माला(fmt + i, "REC->");
			अगर (r && (!c || r < c)) अणु
				/*
				 * Addresses of events on the buffer,
				 * or an array on the buffer is
				 * OK to dereference.
				 * There's ways to fool this, but
				 * this is to catch common mistakes,
				 * not malicious code.
				 */
				a = म_अक्षर(fmt + i, '&');
				अगर ((a && (a < r)) || test_field(r, call))
					dereference_flags &= ~(1ULL << arg);
			पूर्ण
		next_arg:
			i--;
			arg++;
		पूर्ण
	पूर्ण

	/*
	 * If you triggered the below warning, the trace event reported
	 * uses an unsafe dereference poपूर्णांकer %p*. As the data stored
	 * at the trace event समय may no दीर्घer exist when the trace
	 * event is prपूर्णांकed, dereferencing to the original source is
	 * unsafe. The source of the dereference must be copied पूर्णांकo the
	 * event itself, and the dereference must access the copy instead.
	 */
	अगर (WARN_ON_ONCE(dereference_flags)) अणु
		arg = 1;
		जबतक (!(dereference_flags & 1)) अणु
			dereference_flags >>= 1;
			arg++;
		पूर्ण
		pr_warn("event %s has unsafe dereference of argument %d\n",
			trace_event_name(call), arg);
		pr_warn("print_fmt: %s\n", fmt);
	पूर्ण
पूर्ण

पूर्णांक trace_event_raw_init(काष्ठा trace_event_call *call)
अणु
	पूर्णांक id;

	id = रेजिस्टर_trace_event(&call->event);
	अगर (!id)
		वापस -ENODEV;

	test_event_prपूर्णांकk(call);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(trace_event_raw_init);

bool trace_event_ignore_this_pid(काष्ठा trace_event_file *trace_file)
अणु
	काष्ठा trace_array *tr = trace_file->tr;
	काष्ठा trace_array_cpu *data;
	काष्ठा trace_pid_list *no_pid_list;
	काष्ठा trace_pid_list *pid_list;

	pid_list = rcu_dereference_raw(tr->filtered_pids);
	no_pid_list = rcu_dereference_raw(tr->filtered_no_pids);

	अगर (!pid_list && !no_pid_list)
		वापस false;

	data = this_cpu_ptr(tr->array_buffer.data);

	वापस data->ignore_pid;
पूर्ण
EXPORT_SYMBOL_GPL(trace_event_ignore_this_pid);

व्योम *trace_event_buffer_reserve(काष्ठा trace_event_buffer *fbuffer,
				 काष्ठा trace_event_file *trace_file,
				 अचिन्हित दीर्घ len)
अणु
	काष्ठा trace_event_call *event_call = trace_file->event_call;

	अगर ((trace_file->flags & EVENT_खाता_FL_PID_FILTER) &&
	    trace_event_ignore_this_pid(trace_file))
		वापस शून्य;

	/*
	 * If CONFIG_PREEMPTION is enabled, then the tracepoपूर्णांक itself disables
	 * preemption (adding one to the preempt_count). Since we are
	 * पूर्णांकerested in the preempt_count at the समय the tracepoपूर्णांक was
	 * hit, we need to subtract one to offset the increment.
	 */
	fbuffer->trace_ctx = tracing_gen_ctx_dec();
	fbuffer->trace_file = trace_file;

	fbuffer->event =
		trace_event_buffer_lock_reserve(&fbuffer->buffer, trace_file,
						event_call->event.type, len,
						fbuffer->trace_ctx);
	अगर (!fbuffer->event)
		वापस शून्य;

	fbuffer->regs = शून्य;
	fbuffer->entry = ring_buffer_event_data(fbuffer->event);
	वापस fbuffer->entry;
पूर्ण
EXPORT_SYMBOL_GPL(trace_event_buffer_reserve);

पूर्णांक trace_event_reg(काष्ठा trace_event_call *call,
		    क्रमागत trace_reg type, व्योम *data)
अणु
	काष्ठा trace_event_file *file = data;

	WARN_ON(!(call->flags & TRACE_EVENT_FL_TRACEPOINT));
	चयन (type) अणु
	हाल TRACE_REG_REGISTER:
		वापस tracepoपूर्णांक_probe_रेजिस्टर(call->tp,
						 call->class->probe,
						 file);
	हाल TRACE_REG_UNREGISTER:
		tracepoपूर्णांक_probe_unरेजिस्टर(call->tp,
					    call->class->probe,
					    file);
		वापस 0;

#अगर_घोषित CONFIG_PERF_EVENTS
	हाल TRACE_REG_PERF_REGISTER:
		वापस tracepoपूर्णांक_probe_रेजिस्टर(call->tp,
						 call->class->perf_probe,
						 call);
	हाल TRACE_REG_PERF_UNREGISTER:
		tracepoपूर्णांक_probe_unरेजिस्टर(call->tp,
					    call->class->perf_probe,
					    call);
		वापस 0;
	हाल TRACE_REG_PERF_OPEN:
	हाल TRACE_REG_PERF_CLOSE:
	हाल TRACE_REG_PERF_ADD:
	हाल TRACE_REG_PERF_DEL:
		वापस 0;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(trace_event_reg);

व्योम trace_event_enable_cmd_record(bool enable)
अणु
	काष्ठा trace_event_file *file;
	काष्ठा trace_array *tr;

	lockdep_निश्चित_held(&event_mutex);

	करो_क्रम_each_event_file(tr, file) अणु

		अगर (!(file->flags & EVENT_खाता_FL_ENABLED))
			जारी;

		अगर (enable) अणु
			tracing_start_cmdline_record();
			set_bit(EVENT_खाता_FL_RECORDED_CMD_BIT, &file->flags);
		पूर्ण अन्यथा अणु
			tracing_stop_cmdline_record();
			clear_bit(EVENT_खाता_FL_RECORDED_CMD_BIT, &file->flags);
		पूर्ण
	पूर्ण जबतक_क्रम_each_event_file();
पूर्ण

व्योम trace_event_enable_tgid_record(bool enable)
अणु
	काष्ठा trace_event_file *file;
	काष्ठा trace_array *tr;

	lockdep_निश्चित_held(&event_mutex);

	करो_क्रम_each_event_file(tr, file) अणु
		अगर (!(file->flags & EVENT_खाता_FL_ENABLED))
			जारी;

		अगर (enable) अणु
			tracing_start_tgid_record();
			set_bit(EVENT_खाता_FL_RECORDED_TGID_BIT, &file->flags);
		पूर्ण अन्यथा अणु
			tracing_stop_tgid_record();
			clear_bit(EVENT_खाता_FL_RECORDED_TGID_BIT,
				  &file->flags);
		पूर्ण
	पूर्ण जबतक_क्रम_each_event_file();
पूर्ण

अटल पूर्णांक __ftrace_event_enable_disable(काष्ठा trace_event_file *file,
					 पूर्णांक enable, पूर्णांक soft_disable)
अणु
	काष्ठा trace_event_call *call = file->event_call;
	काष्ठा trace_array *tr = file->tr;
	अचिन्हित दीर्घ file_flags = file->flags;
	पूर्णांक ret = 0;
	पूर्णांक disable;

	चयन (enable) अणु
	हाल 0:
		/*
		 * When soft_disable is set and enable is cleared, the sm_ref
		 * reference counter is decremented. If it reaches 0, we want
		 * to clear the SOFT_DISABLED flag but leave the event in the
		 * state that it was. That is, अगर the event was enabled and
		 * SOFT_DISABLED isn't set, then करो nothing. But अगर SOFT_DISABLED
		 * is set we करो not want the event to be enabled beक्रमe we
		 * clear the bit.
		 *
		 * When soft_disable is not set but the SOFT_MODE flag is,
		 * we करो nothing. Do not disable the tracepoपूर्णांक, otherwise
		 * "soft enable"s (clearing the SOFT_DISABLED bit) wont work.
		 */
		अगर (soft_disable) अणु
			अगर (atomic_dec_वापस(&file->sm_ref) > 0)
				अवरोध;
			disable = file->flags & EVENT_खाता_FL_SOFT_DISABLED;
			clear_bit(EVENT_खाता_FL_SOFT_MODE_BIT, &file->flags);
		पूर्ण अन्यथा
			disable = !(file->flags & EVENT_खाता_FL_SOFT_MODE);

		अगर (disable && (file->flags & EVENT_खाता_FL_ENABLED)) अणु
			clear_bit(EVENT_खाता_FL_ENABLED_BIT, &file->flags);
			अगर (file->flags & EVENT_खाता_FL_RECORDED_CMD) अणु
				tracing_stop_cmdline_record();
				clear_bit(EVENT_खाता_FL_RECORDED_CMD_BIT, &file->flags);
			पूर्ण

			अगर (file->flags & EVENT_खाता_FL_RECORDED_TGID) अणु
				tracing_stop_tgid_record();
				clear_bit(EVENT_खाता_FL_RECORDED_TGID_BIT, &file->flags);
			पूर्ण

			call->class->reg(call, TRACE_REG_UNREGISTER, file);
		पूर्ण
		/* If in SOFT_MODE, just set the SOFT_DISABLE_BIT, अन्यथा clear it */
		अगर (file->flags & EVENT_खाता_FL_SOFT_MODE)
			set_bit(EVENT_खाता_FL_SOFT_DISABLED_BIT, &file->flags);
		अन्यथा
			clear_bit(EVENT_खाता_FL_SOFT_DISABLED_BIT, &file->flags);
		अवरोध;
	हाल 1:
		/*
		 * When soft_disable is set and enable is set, we want to
		 * रेजिस्टर the tracepoपूर्णांक क्रम the event, but leave the event
		 * as is. That means, अगर the event was alपढ़ोy enabled, we करो
		 * nothing (but set SOFT_MODE). If the event is disabled, we
		 * set SOFT_DISABLED beक्रमe enabling the event tracepoपूर्णांक, so
		 * it still seems to be disabled.
		 */
		अगर (!soft_disable)
			clear_bit(EVENT_खाता_FL_SOFT_DISABLED_BIT, &file->flags);
		अन्यथा अणु
			अगर (atomic_inc_वापस(&file->sm_ref) > 1)
				अवरोध;
			set_bit(EVENT_खाता_FL_SOFT_MODE_BIT, &file->flags);
		पूर्ण

		अगर (!(file->flags & EVENT_खाता_FL_ENABLED)) अणु
			bool cmd = false, tgid = false;

			/* Keep the event disabled, when going to SOFT_MODE. */
			अगर (soft_disable)
				set_bit(EVENT_खाता_FL_SOFT_DISABLED_BIT, &file->flags);

			अगर (tr->trace_flags & TRACE_ITER_RECORD_CMD) अणु
				cmd = true;
				tracing_start_cmdline_record();
				set_bit(EVENT_खाता_FL_RECORDED_CMD_BIT, &file->flags);
			पूर्ण

			अगर (tr->trace_flags & TRACE_ITER_RECORD_TGID) अणु
				tgid = true;
				tracing_start_tgid_record();
				set_bit(EVENT_खाता_FL_RECORDED_TGID_BIT, &file->flags);
			पूर्ण

			ret = call->class->reg(call, TRACE_REG_REGISTER, file);
			अगर (ret) अणु
				अगर (cmd)
					tracing_stop_cmdline_record();
				अगर (tgid)
					tracing_stop_tgid_record();
				pr_info("event trace: Could not enable event "
					"%s\n", trace_event_name(call));
				अवरोध;
			पूर्ण
			set_bit(EVENT_खाता_FL_ENABLED_BIT, &file->flags);

			/* WAS_ENABLED माला_लो set but never cleared. */
			set_bit(EVENT_खाता_FL_WAS_ENABLED_BIT, &file->flags);
		पूर्ण
		अवरोध;
	पूर्ण

	/* Enable or disable use of trace_buffered_event */
	अगर ((file_flags & EVENT_खाता_FL_SOFT_DISABLED) !=
	    (file->flags & EVENT_खाता_FL_SOFT_DISABLED)) अणु
		अगर (file->flags & EVENT_खाता_FL_SOFT_DISABLED)
			trace_buffered_event_enable();
		अन्यथा
			trace_buffered_event_disable();
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक trace_event_enable_disable(काष्ठा trace_event_file *file,
			       पूर्णांक enable, पूर्णांक soft_disable)
अणु
	वापस __ftrace_event_enable_disable(file, enable, soft_disable);
पूर्ण

अटल पूर्णांक ftrace_event_enable_disable(काष्ठा trace_event_file *file,
				       पूर्णांक enable)
अणु
	वापस __ftrace_event_enable_disable(file, enable, 0);
पूर्ण

अटल व्योम ftrace_clear_events(काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_file *file;

	mutex_lock(&event_mutex);
	list_क्रम_each_entry(file, &tr->events, list) अणु
		ftrace_event_enable_disable(file, 0);
	पूर्ण
	mutex_unlock(&event_mutex);
पूर्ण

अटल व्योम
event_filter_pid_sched_process_निकास(व्योम *data, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_array *tr = data;

	pid_list = rcu_dereference_raw(tr->filtered_pids);
	trace_filter_add_हटाओ_task(pid_list, शून्य, task);

	pid_list = rcu_dereference_raw(tr->filtered_no_pids);
	trace_filter_add_हटाओ_task(pid_list, शून्य, task);
पूर्ण

अटल व्योम
event_filter_pid_sched_process_विभाजन(व्योम *data,
				    काष्ठा task_काष्ठा *self,
				    काष्ठा task_काष्ठा *task)
अणु
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_array *tr = data;

	pid_list = rcu_dereference_sched(tr->filtered_pids);
	trace_filter_add_हटाओ_task(pid_list, self, task);

	pid_list = rcu_dereference_sched(tr->filtered_no_pids);
	trace_filter_add_हटाओ_task(pid_list, self, task);
पूर्ण

व्योम trace_event_follow_विभाजन(काष्ठा trace_array *tr, bool enable)
अणु
	अगर (enable) अणु
		रेजिस्टर_trace_prio_sched_process_विभाजन(event_filter_pid_sched_process_विभाजन,
						       tr, पूर्णांक_न्यून);
		रेजिस्टर_trace_prio_sched_process_मुक्त(event_filter_pid_sched_process_निकास,
						       tr, पूर्णांक_उच्च);
	पूर्ण अन्यथा अणु
		unरेजिस्टर_trace_sched_process_विभाजन(event_filter_pid_sched_process_विभाजन,
						    tr);
		unरेजिस्टर_trace_sched_process_मुक्त(event_filter_pid_sched_process_निकास,
						    tr);
	पूर्ण
पूर्ण

अटल व्योम
event_filter_pid_sched_चयन_probe_pre(व्योम *data, bool preempt,
		    काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
	काष्ठा trace_array *tr = data;
	काष्ठा trace_pid_list *no_pid_list;
	काष्ठा trace_pid_list *pid_list;
	bool ret;

	pid_list = rcu_dereference_sched(tr->filtered_pids);
	no_pid_list = rcu_dereference_sched(tr->filtered_no_pids);

	/*
	 * Sched चयन is funny, as we only want to ignore it
	 * in the notrace हाल अगर both prev and next should be ignored.
	 */
	ret = trace_ignore_this_task(शून्य, no_pid_list, prev) &&
		trace_ignore_this_task(शून्य, no_pid_list, next);

	this_cpu_ग_लिखो(tr->array_buffer.data->ignore_pid, ret ||
		       (trace_ignore_this_task(pid_list, शून्य, prev) &&
			trace_ignore_this_task(pid_list, शून्य, next)));
पूर्ण

अटल व्योम
event_filter_pid_sched_चयन_probe_post(व्योम *data, bool preempt,
		    काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
	काष्ठा trace_array *tr = data;
	काष्ठा trace_pid_list *no_pid_list;
	काष्ठा trace_pid_list *pid_list;

	pid_list = rcu_dereference_sched(tr->filtered_pids);
	no_pid_list = rcu_dereference_sched(tr->filtered_no_pids);

	this_cpu_ग_लिखो(tr->array_buffer.data->ignore_pid,
		       trace_ignore_this_task(pid_list, no_pid_list, next));
पूर्ण

अटल व्योम
event_filter_pid_sched_wakeup_probe_pre(व्योम *data, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा trace_array *tr = data;
	काष्ठा trace_pid_list *no_pid_list;
	काष्ठा trace_pid_list *pid_list;

	/* Nothing to करो अगर we are alपढ़ोy tracing */
	अगर (!this_cpu_पढ़ो(tr->array_buffer.data->ignore_pid))
		वापस;

	pid_list = rcu_dereference_sched(tr->filtered_pids);
	no_pid_list = rcu_dereference_sched(tr->filtered_no_pids);

	this_cpu_ग_लिखो(tr->array_buffer.data->ignore_pid,
		       trace_ignore_this_task(pid_list, no_pid_list, task));
पूर्ण

अटल व्योम
event_filter_pid_sched_wakeup_probe_post(व्योम *data, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा trace_array *tr = data;
	काष्ठा trace_pid_list *no_pid_list;
	काष्ठा trace_pid_list *pid_list;

	/* Nothing to करो अगर we are not tracing */
	अगर (this_cpu_पढ़ो(tr->array_buffer.data->ignore_pid))
		वापस;

	pid_list = rcu_dereference_sched(tr->filtered_pids);
	no_pid_list = rcu_dereference_sched(tr->filtered_no_pids);

	/* Set tracing अगर current is enabled */
	this_cpu_ग_लिखो(tr->array_buffer.data->ignore_pid,
		       trace_ignore_this_task(pid_list, no_pid_list, current));
पूर्ण

अटल व्योम unरेजिस्टर_pid_events(काष्ठा trace_array *tr)
अणु
	unरेजिस्टर_trace_sched_चयन(event_filter_pid_sched_चयन_probe_pre, tr);
	unरेजिस्टर_trace_sched_चयन(event_filter_pid_sched_चयन_probe_post, tr);

	unरेजिस्टर_trace_sched_wakeup(event_filter_pid_sched_wakeup_probe_pre, tr);
	unरेजिस्टर_trace_sched_wakeup(event_filter_pid_sched_wakeup_probe_post, tr);

	unरेजिस्टर_trace_sched_wakeup_new(event_filter_pid_sched_wakeup_probe_pre, tr);
	unरेजिस्टर_trace_sched_wakeup_new(event_filter_pid_sched_wakeup_probe_post, tr);

	unरेजिस्टर_trace_sched_waking(event_filter_pid_sched_wakeup_probe_pre, tr);
	unरेजिस्टर_trace_sched_waking(event_filter_pid_sched_wakeup_probe_post, tr);
पूर्ण

अटल व्योम __ftrace_clear_event_pids(काष्ठा trace_array *tr, पूर्णांक type)
अणु
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_pid_list *no_pid_list;
	काष्ठा trace_event_file *file;
	पूर्णांक cpu;

	pid_list = rcu_dereference_रक्षित(tr->filtered_pids,
					     lockdep_is_held(&event_mutex));
	no_pid_list = rcu_dereference_रक्षित(tr->filtered_no_pids,
					     lockdep_is_held(&event_mutex));

	/* Make sure there's something to करो */
	अगर (!pid_type_enabled(type, pid_list, no_pid_list))
		वापस;

	अगर (!still_need_pid_events(type, pid_list, no_pid_list)) अणु
		unरेजिस्टर_pid_events(tr);

		list_क्रम_each_entry(file, &tr->events, list) अणु
			clear_bit(EVENT_खाता_FL_PID_FILTER_BIT, &file->flags);
		पूर्ण

		क्रम_each_possible_cpu(cpu)
			per_cpu_ptr(tr->array_buffer.data, cpu)->ignore_pid = false;
	पूर्ण

	अगर (type & TRACE_PIDS)
		rcu_assign_poपूर्णांकer(tr->filtered_pids, शून्य);

	अगर (type & TRACE_NO_PIDS)
		rcu_assign_poपूर्णांकer(tr->filtered_no_pids, शून्य);

	/* Wait till all users are no दीर्घer using pid filtering */
	tracepoपूर्णांक_synchronize_unरेजिस्टर();

	अगर ((type & TRACE_PIDS) && pid_list)
		trace_मुक्त_pid_list(pid_list);

	अगर ((type & TRACE_NO_PIDS) && no_pid_list)
		trace_मुक्त_pid_list(no_pid_list);
पूर्ण

अटल व्योम ftrace_clear_event_pids(काष्ठा trace_array *tr, पूर्णांक type)
अणु
	mutex_lock(&event_mutex);
	__ftrace_clear_event_pids(tr, type);
	mutex_unlock(&event_mutex);
पूर्ण

अटल व्योम __put_प्रणाली(काष्ठा event_subप्रणाली *प्रणाली)
अणु
	काष्ठा event_filter *filter = प्रणाली->filter;

	WARN_ON_ONCE(प्रणाली_refcount(प्रणाली) == 0);
	अगर (प्रणाली_refcount_dec(प्रणाली))
		वापस;

	list_del(&प्रणाली->list);

	अगर (filter) अणु
		kमुक्त(filter->filter_string);
		kमुक्त(filter);
	पूर्ण
	kमुक्त_स्थिर(प्रणाली->name);
	kमुक्त(प्रणाली);
पूर्ण

अटल व्योम __get_प्रणाली(काष्ठा event_subप्रणाली *प्रणाली)
अणु
	WARN_ON_ONCE(प्रणाली_refcount(प्रणाली) == 0);
	प्रणाली_refcount_inc(प्रणाली);
पूर्ण

अटल व्योम __get_प्रणाली_dir(काष्ठा trace_subप्रणाली_dir *dir)
अणु
	WARN_ON_ONCE(dir->ref_count == 0);
	dir->ref_count++;
	__get_प्रणाली(dir->subप्रणाली);
पूर्ण

अटल व्योम __put_प्रणाली_dir(काष्ठा trace_subप्रणाली_dir *dir)
अणु
	WARN_ON_ONCE(dir->ref_count == 0);
	/* If the subप्रणाली is about to be मुक्तd, the dir must be too */
	WARN_ON_ONCE(प्रणाली_refcount(dir->subप्रणाली) == 1 && dir->ref_count != 1);

	__put_प्रणाली(dir->subप्रणाली);
	अगर (!--dir->ref_count)
		kमुक्त(dir);
पूर्ण

अटल व्योम put_प्रणाली(काष्ठा trace_subप्रणाली_dir *dir)
अणु
	mutex_lock(&event_mutex);
	__put_प्रणाली_dir(dir);
	mutex_unlock(&event_mutex);
पूर्ण

अटल व्योम हटाओ_subप्रणाली(काष्ठा trace_subप्रणाली_dir *dir)
अणु
	अगर (!dir)
		वापस;

	अगर (!--dir->nr_events) अणु
		tracefs_हटाओ(dir->entry);
		list_del(&dir->list);
		__put_प्रणाली_dir(dir);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_event_file_dir(काष्ठा trace_event_file *file)
अणु
	काष्ठा dentry *dir = file->dir;
	काष्ठा dentry *child;

	अगर (dir) अणु
		spin_lock(&dir->d_lock);	/* probably unneeded */
		list_क्रम_each_entry(child, &dir->d_subdirs, d_child) अणु
			अगर (d_really_is_positive(child))	/* probably unneeded */
				d_inode(child)->i_निजी = शून्य;
		पूर्ण
		spin_unlock(&dir->d_lock);

		tracefs_हटाओ(dir);
	पूर्ण

	list_del(&file->list);
	हटाओ_subप्रणाली(file->प्रणाली);
	मुक्त_event_filter(file->filter);
	kmem_cache_मुक्त(file_cachep, file);
पूर्ण

/*
 * __ftrace_set_clr_event(शून्य, शून्य, शून्य, set) will set/unset all events.
 */
अटल पूर्णांक
__ftrace_set_clr_event_nolock(काष्ठा trace_array *tr, स्थिर अक्षर *match,
			      स्थिर अक्षर *sub, स्थिर अक्षर *event, पूर्णांक set)
अणु
	काष्ठा trace_event_file *file;
	काष्ठा trace_event_call *call;
	स्थिर अक्षर *name;
	पूर्णांक ret = -EINVAL;
	पूर्णांक eret = 0;

	list_क्रम_each_entry(file, &tr->events, list) अणु

		call = file->event_call;
		name = trace_event_name(call);

		अगर (!name || !call->class || !call->class->reg)
			जारी;

		अगर (call->flags & TRACE_EVENT_FL_IGNORE_ENABLE)
			जारी;

		अगर (match &&
		    म_भेद(match, name) != 0 &&
		    म_भेद(match, call->class->प्रणाली) != 0)
			जारी;

		अगर (sub && म_भेद(sub, call->class->प्रणाली) != 0)
			जारी;

		अगर (event && म_भेद(event, name) != 0)
			जारी;

		ret = ftrace_event_enable_disable(file, set);

		/*
		 * Save the first error and वापस that. Some events
		 * may still have been enabled, but let the user
		 * know that something went wrong.
		 */
		अगर (ret && !eret)
			eret = ret;

		ret = eret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __ftrace_set_clr_event(काष्ठा trace_array *tr, स्थिर अक्षर *match,
				  स्थिर अक्षर *sub, स्थिर अक्षर *event, पूर्णांक set)
अणु
	पूर्णांक ret;

	mutex_lock(&event_mutex);
	ret = __ftrace_set_clr_event_nolock(tr, match, sub, event, set);
	mutex_unlock(&event_mutex);

	वापस ret;
पूर्ण

पूर्णांक ftrace_set_clr_event(काष्ठा trace_array *tr, अक्षर *buf, पूर्णांक set)
अणु
	अक्षर *event = शून्य, *sub = शून्य, *match;
	पूर्णांक ret;

	अगर (!tr)
		वापस -ENOENT;
	/*
	 * The buf क्रमmat can be <subप्रणाली>:<event-name>
	 *  *:<event-name> means any event by that name.
	 *  :<event-name> is the same.
	 *
	 *  <subप्रणाली>:* means all events in that subप्रणाली
	 *  <subप्रणाली>: means the same.
	 *
	 *  <name> (no ':') means all events in a subप्रणाली with
	 *  the name <name> or any event that matches <name>
	 */

	match = strsep(&buf, ":");
	अगर (buf) अणु
		sub = match;
		event = buf;
		match = शून्य;

		अगर (!म_माप(sub) || म_भेद(sub, "*") == 0)
			sub = शून्य;
		अगर (!म_माप(event) || म_भेद(event, "*") == 0)
			event = शून्य;
	पूर्ण

	ret = __ftrace_set_clr_event(tr, match, sub, event, set);

	/* Put back the colon to allow this to be called again */
	अगर (buf)
		*(buf - 1) = ':';

	वापस ret;
पूर्ण

/**
 * trace_set_clr_event - enable or disable an event
 * @प्रणाली: प्रणाली name to match (शून्य क्रम any प्रणाली)
 * @event: event name to match (शून्य क्रम all events, within प्रणाली)
 * @set: 1 to enable, 0 to disable
 *
 * This is a way क्रम other parts of the kernel to enable or disable
 * event recording.
 *
 * Returns 0 on success, -EINVAL अगर the parameters करो not match any
 * रेजिस्टरed events.
 */
पूर्णांक trace_set_clr_event(स्थिर अक्षर *प्रणाली, स्थिर अक्षर *event, पूर्णांक set)
अणु
	काष्ठा trace_array *tr = top_trace_array();

	अगर (!tr)
		वापस -ENODEV;

	वापस __ftrace_set_clr_event(tr, शून्य, प्रणाली, event, set);
पूर्ण
EXPORT_SYMBOL_GPL(trace_set_clr_event);

/**
 * trace_array_set_clr_event - enable or disable an event क्रम a trace array.
 * @tr: concerned trace array.
 * @प्रणाली: प्रणाली name to match (शून्य क्रम any प्रणाली)
 * @event: event name to match (शून्य क्रम all events, within प्रणाली)
 * @enable: true to enable, false to disable
 *
 * This is a way क्रम other parts of the kernel to enable or disable
 * event recording.
 *
 * Returns 0 on success, -EINVAL अगर the parameters करो not match any
 * रेजिस्टरed events.
 */
पूर्णांक trace_array_set_clr_event(काष्ठा trace_array *tr, स्थिर अक्षर *प्रणाली,
		स्थिर अक्षर *event, bool enable)
अणु
	पूर्णांक set;

	अगर (!tr)
		वापस -ENOENT;

	set = (enable == true) ? 1 : 0;
	वापस __ftrace_set_clr_event(tr, शून्य, प्रणाली, event, set);
पूर्ण
EXPORT_SYMBOL_GPL(trace_array_set_clr_event);

/* 128 should be much more than enough */
#घोषणा EVENT_BUF_SIZE		127

अटल sमाप_प्रकार
ftrace_event_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
		   माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा trace_parser parser;
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा trace_array *tr = m->निजी;
	sमाप_प्रकार पढ़ो, ret;

	अगर (!cnt)
		वापस 0;

	ret = tracing_update_buffers();
	अगर (ret < 0)
		वापस ret;

	अगर (trace_parser_get_init(&parser, EVENT_BUF_SIZE + 1))
		वापस -ENOMEM;

	पढ़ो = trace_get_user(&parser, ubuf, cnt, ppos);

	अगर (पढ़ो >= 0 && trace_parser_loaded((&parser))) अणु
		पूर्णांक set = 1;

		अगर (*parser.buffer == '!')
			set = 0;

		ret = ftrace_set_clr_event(tr, parser.buffer + !set, set);
		अगर (ret)
			जाओ out_put;
	पूर्ण

	ret = पढ़ो;

 out_put:
	trace_parser_put(&parser);

	वापस ret;
पूर्ण

अटल व्योम *
t_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा trace_event_file *file = v;
	काष्ठा trace_event_call *call;
	काष्ठा trace_array *tr = m->निजी;

	(*pos)++;

	list_क्रम_each_entry_जारी(file, &tr->events, list) अणु
		call = file->event_call;
		/*
		 * The ftrace subप्रणाली is क्रम showing क्रमmats only.
		 * They can not be enabled or disabled via the event files.
		 */
		अगर (call->class && call->class->reg &&
		    !(call->flags & TRACE_EVENT_FL_IGNORE_ENABLE))
			वापस file;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *t_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा trace_event_file *file;
	काष्ठा trace_array *tr = m->निजी;
	loff_t l;

	mutex_lock(&event_mutex);

	file = list_entry(&tr->events, काष्ठा trace_event_file, list);
	क्रम (l = 0; l <= *pos; ) अणु
		file = t_next(m, file, &l);
		अगर (!file)
			अवरोध;
	पूर्ण
	वापस file;
पूर्ण

अटल व्योम *
s_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा trace_event_file *file = v;
	काष्ठा trace_array *tr = m->निजी;

	(*pos)++;

	list_क्रम_each_entry_जारी(file, &tr->events, list) अणु
		अगर (file->flags & EVENT_खाता_FL_ENABLED)
			वापस file;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *s_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा trace_event_file *file;
	काष्ठा trace_array *tr = m->निजी;
	loff_t l;

	mutex_lock(&event_mutex);

	file = list_entry(&tr->events, काष्ठा trace_event_file, list);
	क्रम (l = 0; l <= *pos; ) अणु
		file = s_next(m, file, &l);
		अगर (!file)
			अवरोध;
	पूर्ण
	वापस file;
पूर्ण

अटल पूर्णांक t_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा trace_event_file *file = v;
	काष्ठा trace_event_call *call = file->event_call;

	अगर (म_भेद(call->class->प्रणाली, TRACE_SYSTEM) != 0)
		seq_म_लिखो(m, "%s:", call->class->प्रणाली);
	seq_म_लिखो(m, "%s\n", trace_event_name(call));

	वापस 0;
पूर्ण

अटल व्योम t_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	mutex_unlock(&event_mutex);
पूर्ण

अटल व्योम *
__next(काष्ठा seq_file *m, व्योम *v, loff_t *pos, पूर्णांक type)
अणु
	काष्ठा trace_array *tr = m->निजी;
	काष्ठा trace_pid_list *pid_list;

	अगर (type == TRACE_PIDS)
		pid_list = rcu_dereference_sched(tr->filtered_pids);
	अन्यथा
		pid_list = rcu_dereference_sched(tr->filtered_no_pids);

	वापस trace_pid_next(pid_list, v, pos);
पूर्ण

अटल व्योम *
p_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	वापस __next(m, v, pos, TRACE_PIDS);
पूर्ण

अटल व्योम *
np_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	वापस __next(m, v, pos, TRACE_NO_PIDS);
पूर्ण

अटल व्योम *__start(काष्ठा seq_file *m, loff_t *pos, पूर्णांक type)
	__acquires(RCU)
अणु
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_array *tr = m->निजी;

	/*
	 * Grab the mutex, to keep calls to p_next() having the same
	 * tr->filtered_pids as p_start() has.
	 * If we just passed the tr->filtered_pids around, then RCU would
	 * have been enough, but करोing that makes things more complex.
	 */
	mutex_lock(&event_mutex);
	rcu_पढ़ो_lock_sched();

	अगर (type == TRACE_PIDS)
		pid_list = rcu_dereference_sched(tr->filtered_pids);
	अन्यथा
		pid_list = rcu_dereference_sched(tr->filtered_no_pids);

	अगर (!pid_list)
		वापस शून्य;

	वापस trace_pid_start(pid_list, pos);
पूर्ण

अटल व्योम *p_start(काष्ठा seq_file *m, loff_t *pos)
	__acquires(RCU)
अणु
	वापस __start(m, pos, TRACE_PIDS);
पूर्ण

अटल व्योम *np_start(काष्ठा seq_file *m, loff_t *pos)
	__acquires(RCU)
अणु
	वापस __start(m, pos, TRACE_NO_PIDS);
पूर्ण

अटल व्योम p_stop(काष्ठा seq_file *m, व्योम *p)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock_sched();
	mutex_unlock(&event_mutex);
पूर्ण

अटल sमाप_प्रकार
event_enable_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार cnt,
		  loff_t *ppos)
अणु
	काष्ठा trace_event_file *file;
	अचिन्हित दीर्घ flags;
	अक्षर buf[4] = "0";

	mutex_lock(&event_mutex);
	file = event_file_data(filp);
	अगर (likely(file))
		flags = file->flags;
	mutex_unlock(&event_mutex);

	अगर (!file)
		वापस -ENODEV;

	अगर (flags & EVENT_खाता_FL_ENABLED &&
	    !(flags & EVENT_खाता_FL_SOFT_DISABLED))
		म_नकल(buf, "1");

	अगर (flags & EVENT_खाता_FL_SOFT_DISABLED ||
	    flags & EVENT_खाता_FL_SOFT_MODE)
		म_जोड़ो(buf, "*");

	म_जोड़ो(buf, "\n");

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, म_माप(buf));
पूर्ण

अटल sमाप_प्रकार
event_enable_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf, माप_प्रकार cnt,
		   loff_t *ppos)
अणु
	काष्ठा trace_event_file *file;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	ret = tracing_update_buffers();
	अगर (ret < 0)
		वापस ret;

	चयन (val) अणु
	हाल 0:
	हाल 1:
		ret = -ENODEV;
		mutex_lock(&event_mutex);
		file = event_file_data(filp);
		अगर (likely(file))
			ret = ftrace_event_enable_disable(file, val);
		mutex_unlock(&event_mutex);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	*ppos += cnt;

	वापस ret ? ret : cnt;
पूर्ण

अटल sमाप_प्रकार
प्रणाली_enable_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार cnt,
		   loff_t *ppos)
अणु
	स्थिर अक्षर set_to_अक्षर[4] = अणु '?', '0', '1', 'X' पूर्ण;
	काष्ठा trace_subप्रणाली_dir *dir = filp->निजी_data;
	काष्ठा event_subप्रणाली *प्रणाली = dir->subप्रणाली;
	काष्ठा trace_event_call *call;
	काष्ठा trace_event_file *file;
	काष्ठा trace_array *tr = dir->tr;
	अक्षर buf[2];
	पूर्णांक set = 0;
	पूर्णांक ret;

	mutex_lock(&event_mutex);
	list_क्रम_each_entry(file, &tr->events, list) अणु
		call = file->event_call;
		अगर ((call->flags & TRACE_EVENT_FL_IGNORE_ENABLE) ||
		    !trace_event_name(call) || !call->class || !call->class->reg)
			जारी;

		अगर (प्रणाली && म_भेद(call->class->प्रणाली, प्रणाली->name) != 0)
			जारी;

		/*
		 * We need to find out अगर all the events are set
		 * or अगर all events or cleared, or अगर we have
		 * a mixture.
		 */
		set |= (1 << !!(file->flags & EVENT_खाता_FL_ENABLED));

		/*
		 * If we have a mixture, no need to look further.
		 */
		अगर (set == 3)
			अवरोध;
	पूर्ण
	mutex_unlock(&event_mutex);

	buf[0] = set_to_अक्षर[set];
	buf[1] = '\n';

	ret = simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, 2);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
प्रणाली_enable_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf, माप_प्रकार cnt,
		    loff_t *ppos)
अणु
	काष्ठा trace_subप्रणाली_dir *dir = filp->निजी_data;
	काष्ठा event_subप्रणाली *प्रणाली = dir->subप्रणाली;
	स्थिर अक्षर *name = शून्य;
	अचिन्हित दीर्घ val;
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	ret = tracing_update_buffers();
	अगर (ret < 0)
		वापस ret;

	अगर (val != 0 && val != 1)
		वापस -EINVAL;

	/*
	 * Opening of "enable" adds a ref count to प्रणाली,
	 * so the name is safe to use.
	 */
	अगर (प्रणाली)
		name = प्रणाली->name;

	ret = __ftrace_set_clr_event(dir->tr, शून्य, name, शून्य, val);
	अगर (ret)
		जाओ out;

	ret = cnt;

out:
	*ppos += cnt;

	वापस ret;
पूर्ण

क्रमागत अणु
	FORMAT_HEADER		= 1,
	FORMAT_FIELD_SEPERATOR	= 2,
	FORMAT_PRINTFMT		= 3,
पूर्ण;

अटल व्योम *f_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा trace_event_call *call = event_file_data(m->निजी);
	काष्ठा list_head *common_head = &ftrace_common_fields;
	काष्ठा list_head *head = trace_get_fields(call);
	काष्ठा list_head *node = v;

	(*pos)++;

	चयन ((अचिन्हित दीर्घ)v) अणु
	हाल FORMAT_HEADER:
		node = common_head;
		अवरोध;

	हाल FORMAT_FIELD_SEPERATOR:
		node = head;
		अवरोध;

	हाल FORMAT_PRINTFMT:
		/* all करोne */
		वापस शून्य;
	पूर्ण

	node = node->prev;
	अगर (node == common_head)
		वापस (व्योम *)FORMAT_FIELD_SEPERATOR;
	अन्यथा अगर (node == head)
		वापस (व्योम *)FORMAT_PRINTFMT;
	अन्यथा
		वापस node;
पूर्ण

अटल पूर्णांक f_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा trace_event_call *call = event_file_data(m->निजी);
	काष्ठा ftrace_event_field *field;
	स्थिर अक्षर *array_descriptor;

	चयन ((अचिन्हित दीर्घ)v) अणु
	हाल FORMAT_HEADER:
		seq_म_लिखो(m, "name: %s\n", trace_event_name(call));
		seq_म_लिखो(m, "ID: %d\n", call->event.type);
		seq_माला_दो(m, "format:\n");
		वापस 0;

	हाल FORMAT_FIELD_SEPERATOR:
		seq_अ_दो(m, '\n');
		वापस 0;

	हाल FORMAT_PRINTFMT:
		seq_म_लिखो(m, "\nprint fmt: %s\n",
			   call->prपूर्णांक_fmt);
		वापस 0;
	पूर्ण

	field = list_entry(v, काष्ठा ftrace_event_field, link);
	/*
	 * Smartly shows the array type(except dynamic array).
	 * Normal:
	 *	field:TYPE VAR
	 * If TYPE := TYPE[LEN], it is shown:
	 *	field:TYPE VAR[LEN]
	 */
	array_descriptor = म_अक्षर(field->type, '[');

	अगर (str_has_prefix(field->type, "__data_loc"))
		array_descriptor = शून्य;

	अगर (!array_descriptor)
		seq_म_लिखो(m, "\tfield:%s %s;\toffset:%u;\tsize:%u;\tsigned:%d;\n",
			   field->type, field->name, field->offset,
			   field->size, !!field->is_चिन्हित);
	अन्यथा
		seq_म_लिखो(m, "\tfield:%.*s %s%s;\toffset:%u;\tsize:%u;\tsigned:%d;\n",
			   (पूर्णांक)(array_descriptor - field->type),
			   field->type, field->name,
			   array_descriptor, field->offset,
			   field->size, !!field->is_चिन्हित);

	वापस 0;
पूर्ण

अटल व्योम *f_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	व्योम *p = (व्योम *)FORMAT_HEADER;
	loff_t l = 0;

	/* ->stop() is called even अगर ->start() fails */
	mutex_lock(&event_mutex);
	अगर (!event_file_data(m->निजी))
		वापस ERR_PTR(-ENODEV);

	जबतक (l < *pos && p)
		p = f_next(m, p, &l);

	वापस p;
पूर्ण

अटल व्योम f_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	mutex_unlock(&event_mutex);
पूर्ण

अटल स्थिर काष्ठा seq_operations trace_क्रमmat_seq_ops = अणु
	.start		= f_start,
	.next		= f_next,
	.stop		= f_stop,
	.show		= f_show,
पूर्ण;

अटल पूर्णांक trace_क्रमmat_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m;
	पूर्णांक ret;

	/* Do we want to hide event क्रमmat files on tracefs lockकरोwn? */

	ret = seq_खोलो(file, &trace_क्रमmat_seq_ops);
	अगर (ret < 0)
		वापस ret;

	m = file->निजी_data;
	m->निजी = file;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
event_id_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार cnt, loff_t *ppos)
अणु
	पूर्णांक id = (दीर्घ)event_file_data(filp);
	अक्षर buf[32];
	पूर्णांक len;

	अगर (unlikely(!id))
		वापस -ENODEV;

	len = प्र_लिखो(buf, "%d\n", id);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार
event_filter_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार cnt,
		  loff_t *ppos)
अणु
	काष्ठा trace_event_file *file;
	काष्ठा trace_seq *s;
	पूर्णांक r = -ENODEV;

	अगर (*ppos)
		वापस 0;

	s = kदो_स्मृति(माप(*s), GFP_KERNEL);

	अगर (!s)
		वापस -ENOMEM;

	trace_seq_init(s);

	mutex_lock(&event_mutex);
	file = event_file_data(filp);
	अगर (file)
		prपूर्णांक_event_filter(file, s);
	mutex_unlock(&event_mutex);

	अगर (file)
		r = simple_पढ़ो_from_buffer(ubuf, cnt, ppos,
					    s->buffer, trace_seq_used(s));

	kमुक्त(s);

	वापस r;
पूर्ण

अटल sमाप_प्रकार
event_filter_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf, माप_प्रकार cnt,
		   loff_t *ppos)
अणु
	काष्ठा trace_event_file *file;
	अक्षर *buf;
	पूर्णांक err = -ENODEV;

	अगर (cnt >= PAGE_SIZE)
		वापस -EINVAL;

	buf = memdup_user_nul(ubuf, cnt);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	mutex_lock(&event_mutex);
	file = event_file_data(filp);
	अगर (file)
		err = apply_event_filter(file, buf);
	mutex_unlock(&event_mutex);

	kमुक्त(buf);
	अगर (err < 0)
		वापस err;

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल LIST_HEAD(event_subप्रणालीs);

अटल पूर्णांक subप्रणाली_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा event_subप्रणाली *प्रणाली = शून्य;
	काष्ठा trace_subप्रणाली_dir *dir = शून्य; /* Initialize क्रम gcc */
	काष्ठा trace_array *tr;
	पूर्णांक ret;

	अगर (tracing_is_disabled())
		वापस -ENODEV;

	/* Make sure the प्रणाली still exists */
	mutex_lock(&event_mutex);
	mutex_lock(&trace_types_lock);
	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु
		list_क्रम_each_entry(dir, &tr->प्रणालीs, list) अणु
			अगर (dir == inode->i_निजी) अणु
				/* Don't खोलो प्रणालीs with no events */
				अगर (dir->nr_events) अणु
					__get_प्रणाली_dir(dir);
					प्रणाली = dir->subप्रणाली;
				पूर्ण
				जाओ निकास_loop;
			पूर्ण
		पूर्ण
	पूर्ण
 निकास_loop:
	mutex_unlock(&trace_types_lock);
	mutex_unlock(&event_mutex);

	अगर (!प्रणाली)
		वापस -ENODEV;

	/* Some versions of gcc think dir can be uninitialized here */
	WARN_ON(!dir);

	/* Still need to increment the ref count of the प्रणाली */
	अगर (trace_array_get(tr) < 0) अणु
		put_प्रणाली(dir);
		वापस -ENODEV;
	पूर्ण

	ret = tracing_खोलो_generic(inode, filp);
	अगर (ret < 0) अणु
		trace_array_put(tr);
		put_प्रणाली(dir);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक प्रणाली_tr_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा trace_subप्रणाली_dir *dir;
	काष्ठा trace_array *tr = inode->i_निजी;
	पूर्णांक ret;

	/* Make a temporary dir that has no प्रणाली but poपूर्णांकs to tr */
	dir = kzalloc(माप(*dir), GFP_KERNEL);
	अगर (!dir)
		वापस -ENOMEM;

	ret = tracing_खोलो_generic_tr(inode, filp);
	अगर (ret < 0) अणु
		kमुक्त(dir);
		वापस ret;
	पूर्ण
	dir->tr = tr;
	filp->निजी_data = dir;

	वापस 0;
पूर्ण

अटल पूर्णांक subप्रणाली_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_subप्रणाली_dir *dir = file->निजी_data;

	trace_array_put(dir->tr);

	/*
	 * If dir->subप्रणाली is शून्य, then this is a temporary
	 * descriptor that was made क्रम a trace_array to enable
	 * all subप्रणालीs.
	 */
	अगर (dir->subप्रणाली)
		put_प्रणाली(dir);
	अन्यथा
		kमुक्त(dir);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
subप्रणाली_filter_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार cnt,
		      loff_t *ppos)
अणु
	काष्ठा trace_subप्रणाली_dir *dir = filp->निजी_data;
	काष्ठा event_subप्रणाली *प्रणाली = dir->subप्रणाली;
	काष्ठा trace_seq *s;
	पूर्णांक r;

	अगर (*ppos)
		वापस 0;

	s = kदो_स्मृति(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	trace_seq_init(s);

	prपूर्णांक_subप्रणाली_event_filter(प्रणाली, s);
	r = simple_पढ़ो_from_buffer(ubuf, cnt, ppos,
				    s->buffer, trace_seq_used(s));

	kमुक्त(s);

	वापस r;
पूर्ण

अटल sमाप_प्रकार
subप्रणाली_filter_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf, माप_प्रकार cnt,
		       loff_t *ppos)
अणु
	काष्ठा trace_subप्रणाली_dir *dir = filp->निजी_data;
	अक्षर *buf;
	पूर्णांक err;

	अगर (cnt >= PAGE_SIZE)
		वापस -EINVAL;

	buf = memdup_user_nul(ubuf, cnt);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	err = apply_subप्रणाली_event_filter(dir, buf);
	kमुक्त(buf);
	अगर (err < 0)
		वापस err;

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल sमाप_प्रकार
show_header(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार cnt, loff_t *ppos)
अणु
	पूर्णांक (*func)(काष्ठा trace_seq *s) = filp->निजी_data;
	काष्ठा trace_seq *s;
	पूर्णांक r;

	अगर (*ppos)
		वापस 0;

	s = kदो_स्मृति(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	trace_seq_init(s);

	func(s);
	r = simple_पढ़ो_from_buffer(ubuf, cnt, ppos,
				    s->buffer, trace_seq_used(s));

	kमुक्त(s);

	वापस r;
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
	pid_list = rcu_dereference_रक्षित(tr->filtered_pids,
					     mutex_is_locked(&event_mutex));
	no_pid_list = rcu_dereference_रक्षित(tr->filtered_no_pids,
					     mutex_is_locked(&event_mutex));

	this_cpu_ग_लिखो(tr->array_buffer.data->ignore_pid,
		       trace_ignore_this_task(pid_list, no_pid_list, current));
पूर्ण

अटल व्योम रेजिस्टर_pid_events(काष्ठा trace_array *tr)
अणु
	/*
	 * Register a probe that is called beक्रमe all other probes
	 * to set ignore_pid अगर next or prev करो not match.
	 * Register a probe this is called after all other probes
	 * to only keep ignore_pid set अगर next pid matches.
	 */
	रेजिस्टर_trace_prio_sched_चयन(event_filter_pid_sched_चयन_probe_pre,
					 tr, पूर्णांक_उच्च);
	रेजिस्टर_trace_prio_sched_चयन(event_filter_pid_sched_चयन_probe_post,
					 tr, 0);

	रेजिस्टर_trace_prio_sched_wakeup(event_filter_pid_sched_wakeup_probe_pre,
					 tr, पूर्णांक_उच्च);
	रेजिस्टर_trace_prio_sched_wakeup(event_filter_pid_sched_wakeup_probe_post,
					 tr, 0);

	रेजिस्टर_trace_prio_sched_wakeup_new(event_filter_pid_sched_wakeup_probe_pre,
					     tr, पूर्णांक_उच्च);
	रेजिस्टर_trace_prio_sched_wakeup_new(event_filter_pid_sched_wakeup_probe_post,
					     tr, 0);

	रेजिस्टर_trace_prio_sched_waking(event_filter_pid_sched_wakeup_probe_pre,
					 tr, पूर्णांक_उच्च);
	रेजिस्टर_trace_prio_sched_waking(event_filter_pid_sched_wakeup_probe_post,
					 tr, 0);
पूर्ण

अटल sमाप_प्रकार
event_pid_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		माप_प्रकार cnt, loff_t *ppos, पूर्णांक type)
अणु
	काष्ठा seq_file *m = filp->निजी_data;
	काष्ठा trace_array *tr = m->निजी;
	काष्ठा trace_pid_list *filtered_pids = शून्य;
	काष्ठा trace_pid_list *other_pids = शून्य;
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_event_file *file;
	sमाप_प्रकार ret;

	अगर (!cnt)
		वापस 0;

	ret = tracing_update_buffers();
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&event_mutex);

	अगर (type == TRACE_PIDS) अणु
		filtered_pids = rcu_dereference_रक्षित(tr->filtered_pids,
							  lockdep_is_held(&event_mutex));
		other_pids = rcu_dereference_रक्षित(tr->filtered_no_pids,
							  lockdep_is_held(&event_mutex));
	पूर्ण अन्यथा अणु
		filtered_pids = rcu_dereference_रक्षित(tr->filtered_no_pids,
							  lockdep_is_held(&event_mutex));
		other_pids = rcu_dereference_रक्षित(tr->filtered_pids,
							  lockdep_is_held(&event_mutex));
	पूर्ण

	ret = trace_pid_ग_लिखो(filtered_pids, &pid_list, ubuf, cnt);
	अगर (ret < 0)
		जाओ out;

	अगर (type == TRACE_PIDS)
		rcu_assign_poपूर्णांकer(tr->filtered_pids, pid_list);
	अन्यथा
		rcu_assign_poपूर्णांकer(tr->filtered_no_pids, pid_list);

	list_क्रम_each_entry(file, &tr->events, list) अणु
		set_bit(EVENT_खाता_FL_PID_FILTER_BIT, &file->flags);
	पूर्ण

	अगर (filtered_pids) अणु
		tracepoपूर्णांक_synchronize_unरेजिस्टर();
		trace_मुक्त_pid_list(filtered_pids);
	पूर्ण अन्यथा अगर (pid_list && !other_pids) अणु
		रेजिस्टर_pid_events(tr);
	पूर्ण

	/*
	 * Ignoring of pids is करोne at task चयन. But we have to
	 * check क्रम those tasks that are currently running.
	 * Always करो this in हाल a pid was appended or हटाओd.
	 */
	on_each_cpu(ignore_task_cpu, tr, 1);

 out:
	mutex_unlock(&event_mutex);

	अगर (ret > 0)
		*ppos += ret;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
ftrace_event_pid_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		       माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस event_pid_ग_लिखो(filp, ubuf, cnt, ppos, TRACE_PIDS);
पूर्ण

अटल sमाप_प्रकार
ftrace_event_npid_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
			माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस event_pid_ग_लिखो(filp, ubuf, cnt, ppos, TRACE_NO_PIDS);
पूर्ण

अटल पूर्णांक ftrace_event_avail_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक ftrace_event_set_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक ftrace_event_set_pid_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक ftrace_event_set_npid_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक ftrace_event_release(काष्ठा inode *inode, काष्ठा file *file);

अटल स्थिर काष्ठा seq_operations show_event_seq_ops = अणु
	.start = t_start,
	.next = t_next,
	.show = t_show,
	.stop = t_stop,
पूर्ण;

अटल स्थिर काष्ठा seq_operations show_set_event_seq_ops = अणु
	.start = s_start,
	.next = s_next,
	.show = t_show,
	.stop = t_stop,
पूर्ण;

अटल स्थिर काष्ठा seq_operations show_set_pid_seq_ops = अणु
	.start = p_start,
	.next = p_next,
	.show = trace_pid_show,
	.stop = p_stop,
पूर्ण;

अटल स्थिर काष्ठा seq_operations show_set_no_pid_seq_ops = अणु
	.start = np_start,
	.next = np_next,
	.show = trace_pid_show,
	.stop = p_stop,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_avail_fops = अणु
	.खोलो = ftrace_event_avail_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_set_event_fops = अणु
	.खोलो = ftrace_event_set_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = ftrace_event_ग_लिखो,
	.llseek = seq_lseek,
	.release = ftrace_event_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_set_event_pid_fops = अणु
	.खोलो = ftrace_event_set_pid_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = ftrace_event_pid_ग_लिखो,
	.llseek = seq_lseek,
	.release = ftrace_event_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_set_event_notrace_pid_fops = अणु
	.खोलो = ftrace_event_set_npid_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = ftrace_event_npid_ग_लिखो,
	.llseek = seq_lseek,
	.release = ftrace_event_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_enable_fops = अणु
	.खोलो = tracing_खोलो_generic,
	.पढ़ो = event_enable_पढ़ो,
	.ग_लिखो = event_enable_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_event_क्रमmat_fops = अणु
	.खोलो = trace_क्रमmat_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_event_id_fops = अणु
	.पढ़ो = event_id_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_event_filter_fops = अणु
	.खोलो = tracing_खोलो_generic,
	.पढ़ो = event_filter_पढ़ो,
	.ग_लिखो = event_filter_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_subप्रणाली_filter_fops = अणु
	.खोलो = subप्रणाली_खोलो,
	.पढ़ो = subप्रणाली_filter_पढ़ो,
	.ग_लिखो = subप्रणाली_filter_ग_लिखो,
	.llseek = शेष_llseek,
	.release = subप्रणाली_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_प्रणाली_enable_fops = अणु
	.खोलो = subप्रणाली_खोलो,
	.पढ़ो = प्रणाली_enable_पढ़ो,
	.ग_लिखो = प्रणाली_enable_ग_लिखो,
	.llseek = शेष_llseek,
	.release = subप्रणाली_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_tr_enable_fops = अणु
	.खोलो = प्रणाली_tr_खोलो,
	.पढ़ो = प्रणाली_enable_पढ़ो,
	.ग_लिखो = प्रणाली_enable_ग_लिखो,
	.llseek = शेष_llseek,
	.release = subप्रणाली_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_show_header_fops = अणु
	.खोलो = tracing_खोलो_generic,
	.पढ़ो = show_header,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक
ftrace_event_खोलो(काष्ठा inode *inode, काष्ठा file *file,
		  स्थिर काष्ठा seq_operations *seq_ops)
अणु
	काष्ठा seq_file *m;
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	ret = seq_खोलो(file, seq_ops);
	अगर (ret < 0)
		वापस ret;
	m = file->निजी_data;
	/* copy tr over to seq ops */
	m->निजी = inode->i_निजी;

	वापस ret;
पूर्ण

अटल पूर्णांक ftrace_event_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;

	trace_array_put(tr);

	वापस seq_release(inode, file);
पूर्ण

अटल पूर्णांक
ftrace_event_avail_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर काष्ठा seq_operations *seq_ops = &show_event_seq_ops;

	/* Checks क्रम tracefs lockकरोwn */
	वापस ftrace_event_खोलो(inode, file, seq_ops);
पूर्ण

अटल पूर्णांक
ftrace_event_set_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर काष्ठा seq_operations *seq_ops = &show_set_event_seq_ops;
	काष्ठा trace_array *tr = inode->i_निजी;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	अगर ((file->f_mode & FMODE_WRITE) &&
	    (file->f_flags & O_TRUNC))
		ftrace_clear_events(tr);

	ret = ftrace_event_खोलो(inode, file, seq_ops);
	अगर (ret < 0)
		trace_array_put(tr);
	वापस ret;
पूर्ण

अटल पूर्णांक
ftrace_event_set_pid_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर काष्ठा seq_operations *seq_ops = &show_set_pid_seq_ops;
	काष्ठा trace_array *tr = inode->i_निजी;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	अगर ((file->f_mode & FMODE_WRITE) &&
	    (file->f_flags & O_TRUNC))
		ftrace_clear_event_pids(tr, TRACE_PIDS);

	ret = ftrace_event_खोलो(inode, file, seq_ops);
	अगर (ret < 0)
		trace_array_put(tr);
	वापस ret;
पूर्ण

अटल पूर्णांक
ftrace_event_set_npid_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर काष्ठा seq_operations *seq_ops = &show_set_no_pid_seq_ops;
	काष्ठा trace_array *tr = inode->i_निजी;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	अगर ((file->f_mode & FMODE_WRITE) &&
	    (file->f_flags & O_TRUNC))
		ftrace_clear_event_pids(tr, TRACE_NO_PIDS);

	ret = ftrace_event_खोलो(inode, file, seq_ops);
	अगर (ret < 0)
		trace_array_put(tr);
	वापस ret;
पूर्ण

अटल काष्ठा event_subप्रणाली *
create_new_subप्रणाली(स्थिर अक्षर *name)
अणु
	काष्ठा event_subप्रणाली *प्रणाली;

	/* need to create new entry */
	प्रणाली = kदो_स्मृति(माप(*प्रणाली), GFP_KERNEL);
	अगर (!प्रणाली)
		वापस शून्य;

	प्रणाली->ref_count = 1;

	/* Only allocate अगर dynamic (kprobes and modules) */
	प्रणाली->name = kstrdup_स्थिर(name, GFP_KERNEL);
	अगर (!प्रणाली->name)
		जाओ out_मुक्त;

	प्रणाली->filter = शून्य;

	प्रणाली->filter = kzalloc(माप(काष्ठा event_filter), GFP_KERNEL);
	अगर (!प्रणाली->filter)
		जाओ out_मुक्त;

	list_add(&प्रणाली->list, &event_subप्रणालीs);

	वापस प्रणाली;

 out_मुक्त:
	kमुक्त_स्थिर(प्रणाली->name);
	kमुक्त(प्रणाली);
	वापस शून्य;
पूर्ण

अटल काष्ठा dentry *
event_subप्रणाली_dir(काष्ठा trace_array *tr, स्थिर अक्षर *name,
		    काष्ठा trace_event_file *file, काष्ठा dentry *parent)
अणु
	काष्ठा trace_subप्रणाली_dir *dir;
	काष्ठा event_subप्रणाली *प्रणाली;
	काष्ठा dentry *entry;

	/* First see अगर we did not alपढ़ोy create this dir */
	list_क्रम_each_entry(dir, &tr->प्रणालीs, list) अणु
		प्रणाली = dir->subप्रणाली;
		अगर (म_भेद(प्रणाली->name, name) == 0) अणु
			dir->nr_events++;
			file->प्रणाली = dir;
			वापस dir->entry;
		पूर्ण
	पूर्ण

	/* Now see अगर the प्रणाली itself exists. */
	list_क्रम_each_entry(प्रणाली, &event_subप्रणालीs, list) अणु
		अगर (म_भेद(प्रणाली->name, name) == 0)
			अवरोध;
	पूर्ण
	/* Reset प्रणाली variable when not found */
	अगर (&प्रणाली->list == &event_subप्रणालीs)
		प्रणाली = शून्य;

	dir = kदो_स्मृति(माप(*dir), GFP_KERNEL);
	अगर (!dir)
		जाओ out_fail;

	अगर (!प्रणाली) अणु
		प्रणाली = create_new_subप्रणाली(name);
		अगर (!प्रणाली)
			जाओ out_मुक्त;
	पूर्ण अन्यथा
		__get_प्रणाली(प्रणाली);

	dir->entry = tracefs_create_dir(name, parent);
	अगर (!dir->entry) अणु
		pr_warn("Failed to create system directory %s\n", name);
		__put_प्रणाली(प्रणाली);
		जाओ out_मुक्त;
	पूर्ण

	dir->tr = tr;
	dir->ref_count = 1;
	dir->nr_events = 1;
	dir->subप्रणाली = प्रणाली;
	file->प्रणाली = dir;

	/* the ftrace प्रणाली is special, करो not create enable or filter files */
	अगर (म_भेद(name, "ftrace") != 0) अणु

		entry = tracefs_create_file("filter", 0644, dir->entry, dir,
					    &ftrace_subप्रणाली_filter_fops);
		अगर (!entry) अणु
			kमुक्त(प्रणाली->filter);
			प्रणाली->filter = शून्य;
			pr_warn("Could not create tracefs '%s/filter' entry\n", name);
		पूर्ण

		trace_create_file("enable", 0644, dir->entry, dir,
				  &ftrace_प्रणाली_enable_fops);
	पूर्ण

	list_add(&dir->list, &tr->प्रणालीs);

	वापस dir->entry;

 out_मुक्त:
	kमुक्त(dir);
 out_fail:
	/* Only prपूर्णांक this message अगर failed on memory allocation */
	अगर (!dir || !प्रणाली)
		pr_warn("No memory to create event subsystem %s\n", name);
	वापस शून्य;
पूर्ण

अटल पूर्णांक
event_define_fields(काष्ठा trace_event_call *call)
अणु
	काष्ठा list_head *head;
	पूर्णांक ret = 0;

	/*
	 * Other events may have the same class. Only update
	 * the fields अगर they are not alपढ़ोy defined.
	 */
	head = trace_get_fields(call);
	अगर (list_empty(head)) अणु
		काष्ठा trace_event_fields *field = call->class->fields_array;
		अचिन्हित पूर्णांक offset = माप(काष्ठा trace_entry);

		क्रम (; field->type; field++) अणु
			अगर (field->type == TRACE_FUNCTION_TYPE) अणु
				field->define_fields(call);
				अवरोध;
			पूर्ण

			offset = ALIGN(offset, field->align);
			ret = trace_define_field(call, field->type, field->name,
						 offset, field->size,
						 field->is_चिन्हित, field->filter_type);
			अगर (WARN_ON_ONCE(ret)) अणु
				pr_err("error code is %d\n", ret);
				अवरोध;
			पूर्ण

			offset += field->size;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
event_create_dir(काष्ठा dentry *parent, काष्ठा trace_event_file *file)
अणु
	काष्ठा trace_event_call *call = file->event_call;
	काष्ठा trace_array *tr = file->tr;
	काष्ठा dentry *d_events;
	स्थिर अक्षर *name;
	पूर्णांक ret;

	/*
	 * If the trace poपूर्णांक header did not define TRACE_SYSTEM
	 * then the प्रणाली would be called "TRACE_SYSTEM".
	 */
	अगर (म_भेद(call->class->प्रणाली, TRACE_SYSTEM) != 0) अणु
		d_events = event_subप्रणाली_dir(tr, call->class->प्रणाली, file, parent);
		अगर (!d_events)
			वापस -ENOMEM;
	पूर्ण अन्यथा
		d_events = parent;

	name = trace_event_name(call);
	file->dir = tracefs_create_dir(name, d_events);
	अगर (!file->dir) अणु
		pr_warn("Could not create tracefs '%s' directory\n", name);
		वापस -1;
	पूर्ण

	अगर (call->class->reg && !(call->flags & TRACE_EVENT_FL_IGNORE_ENABLE))
		trace_create_file("enable", 0644, file->dir, file,
				  &ftrace_enable_fops);

#अगर_घोषित CONFIG_PERF_EVENTS
	अगर (call->event.type && call->class->reg)
		trace_create_file("id", 0444, file->dir,
				  (व्योम *)(दीर्घ)call->event.type,
				  &ftrace_event_id_fops);
#पूर्ण_अगर

	ret = event_define_fields(call);
	अगर (ret < 0) अणु
		pr_warn("Could not initialize trace point events/%s\n", name);
		वापस ret;
	पूर्ण

	/*
	 * Only event directories that can be enabled should have
	 * triggers or filters.
	 */
	अगर (!(call->flags & TRACE_EVENT_FL_IGNORE_ENABLE)) अणु
		trace_create_file("filter", 0644, file->dir, file,
				  &ftrace_event_filter_fops);

		trace_create_file("trigger", 0644, file->dir, file,
				  &event_trigger_fops);
	पूर्ण

#अगर_घोषित CONFIG_HIST_TRIGGERS
	trace_create_file("hist", 0444, file->dir, file,
			  &event_hist_fops);
#पूर्ण_अगर
#अगर_घोषित CONFIG_HIST_TRIGGERS_DEBUG
	trace_create_file("hist_debug", 0444, file->dir, file,
			  &event_hist_debug_fops);
#पूर्ण_अगर
	trace_create_file("format", 0444, file->dir, call,
			  &ftrace_event_क्रमmat_fops);

#अगर_घोषित CONFIG_TRACE_EVENT_INJECT
	अगर (call->event.type && call->class->reg)
		trace_create_file("inject", 0200, file->dir, file,
				  &event_inject_fops);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम हटाओ_event_from_tracers(काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_event_file *file;
	काष्ठा trace_array *tr;

	करो_क्रम_each_event_file_safe(tr, file) अणु
		अगर (file->event_call != call)
			जारी;

		हटाओ_event_file_dir(file);
		/*
		 * The करो_क्रम_each_event_file_safe() is
		 * a द्विगुन loop. After finding the call क्रम this
		 * trace_array, we use अवरोध to jump to the next
		 * trace_array.
		 */
		अवरोध;
	पूर्ण जबतक_क्रम_each_event_file();
पूर्ण

अटल व्योम event_हटाओ(काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_array *tr;
	काष्ठा trace_event_file *file;

	करो_क्रम_each_event_file(tr, file) अणु
		अगर (file->event_call != call)
			जारी;

		अगर (file->flags & EVENT_खाता_FL_WAS_ENABLED)
			tr->clear_trace = true;

		ftrace_event_enable_disable(file, 0);
		/*
		 * The करो_क्रम_each_event_file() is
		 * a द्विगुन loop. After finding the call क्रम this
		 * trace_array, we use अवरोध to jump to the next
		 * trace_array.
		 */
		अवरोध;
	पूर्ण जबतक_क्रम_each_event_file();

	अगर (call->event.funcs)
		__unरेजिस्टर_trace_event(&call->event);
	हटाओ_event_from_tracers(call);
	list_del(&call->list);
पूर्ण

अटल पूर्णांक event_init(काष्ठा trace_event_call *call)
अणु
	पूर्णांक ret = 0;
	स्थिर अक्षर *name;

	name = trace_event_name(call);
	अगर (WARN_ON(!name))
		वापस -EINVAL;

	अगर (call->class->raw_init) अणु
		ret = call->class->raw_init(call);
		अगर (ret < 0 && ret != -ENOSYS)
			pr_warn("Could not initialize trace events/%s\n", name);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
__रेजिस्टर_event(काष्ठा trace_event_call *call, काष्ठा module *mod)
अणु
	पूर्णांक ret;

	ret = event_init(call);
	अगर (ret < 0)
		वापस ret;

	list_add(&call->list, &ftrace_events);
	call->mod = mod;

	वापस 0;
पूर्ण

अटल अक्षर *eval_replace(अक्षर *ptr, काष्ठा trace_eval_map *map, पूर्णांक len)
अणु
	पूर्णांक rlen;
	पूर्णांक elen;

	/* Find the length of the eval value as a string */
	elen = snम_लिखो(ptr, 0, "%ld", map->eval_value);
	/* Make sure there's enough room to replace the string with the value */
	अगर (len < elen)
		वापस शून्य;

	snम_लिखो(ptr, elen + 1, "%ld", map->eval_value);

	/* Get the rest of the string of ptr */
	rlen = म_माप(ptr + len);
	स_हटाओ(ptr + elen, ptr + len, rlen);
	/* Make sure we end the new string */
	ptr[elen + rlen] = 0;

	वापस ptr + elen;
पूर्ण

अटल व्योम update_event_prपूर्णांकk(काष्ठा trace_event_call *call,
				काष्ठा trace_eval_map *map)
अणु
	अक्षर *ptr;
	पूर्णांक quote = 0;
	पूर्णांक len = म_माप(map->eval_string);

	क्रम (ptr = call->prपूर्णांक_fmt; *ptr; ptr++) अणु
		अगर (*ptr == '\\') अणु
			ptr++;
			/* paranoid */
			अगर (!*ptr)
				अवरोध;
			जारी;
		पूर्ण
		अगर (*ptr == '"') अणु
			quote ^= 1;
			जारी;
		पूर्ण
		अगर (quote)
			जारी;
		अगर (है_अंक(*ptr)) अणु
			/* skip numbers */
			करो अणु
				ptr++;
				/* Check क्रम alpha अक्षरs like ULL */
			पूर्ण जबतक (है_अक्षर_अंक(*ptr));
			अगर (!*ptr)
				अवरोध;
			/*
			 * A number must have some kind of delimiter after
			 * it, and we can ignore that too.
			 */
			जारी;
		पूर्ण
		अगर (है_अक्षर(*ptr) || *ptr == '_') अणु
			अगर (म_भेदन(map->eval_string, ptr, len) == 0 &&
			    !है_अक्षर_अंक(ptr[len]) && ptr[len] != '_') अणु
				ptr = eval_replace(ptr, map, len);
				/* क्रमागत/माप string smaller than value */
				अगर (WARN_ON_ONCE(!ptr))
					वापस;
				/*
				 * No need to decrement here, as eval_replace()
				 * वापसs the poपूर्णांकer to the अक्षरacter passed
				 * the eval, and two evals can not be placed
				 * back to back without something in between.
				 * We can skip that something in between.
				 */
				जारी;
			पूर्ण
		skip_more:
			करो अणु
				ptr++;
			पूर्ण जबतक (है_अक्षर_अंक(*ptr) || *ptr == '_');
			अगर (!*ptr)
				अवरोध;
			/*
			 * If what comes after this variable is a '.' or
			 * '->' then we can जारी to ignore that string.
			 */
			अगर (*ptr == '.' || (ptr[0] == '-' && ptr[1] == '>')) अणु
				ptr += *ptr == '.' ? 1 : 2;
				अगर (!*ptr)
					अवरोध;
				जाओ skip_more;
			पूर्ण
			/*
			 * Once again, we can skip the delimiter that came
			 * after the string.
			 */
			जारी;
		पूर्ण
	पूर्ण
पूर्ण

व्योम trace_event_eval_update(काष्ठा trace_eval_map **map, पूर्णांक len)
अणु
	काष्ठा trace_event_call *call, *p;
	स्थिर अक्षर *last_प्रणाली = शून्य;
	bool first = false;
	पूर्णांक last_i;
	पूर्णांक i;

	करोwn_ग_लिखो(&trace_event_sem);
	list_क्रम_each_entry_safe(call, p, &ftrace_events, list) अणु
		/* events are usually grouped together with प्रणालीs */
		अगर (!last_प्रणाली || call->class->प्रणाली != last_प्रणाली) अणु
			first = true;
			last_i = 0;
			last_प्रणाली = call->class->प्रणाली;
		पूर्ण

		/*
		 * Since calls are grouped by प्रणालीs, the likelihood that the
		 * next call in the iteration beदीर्घs to the same प्रणाली as the
		 * previous call is high. As an optimization, we skip searching
		 * क्रम a map[] that matches the call's प्रणाली अगर the last call
		 * was from the same प्रणाली. That's what last_i is क्रम. If the
		 * call has the same प्रणाली as the previous call, then last_i
		 * will be the index of the first map[] that has a matching
		 * प्रणाली.
		 */
		क्रम (i = last_i; i < len; i++) अणु
			अगर (call->class->प्रणाली == map[i]->प्रणाली) अणु
				/* Save the first प्रणाली अगर need be */
				अगर (first) अणु
					last_i = i;
					first = false;
				पूर्ण
				update_event_prपूर्णांकk(call, map[i]);
			पूर्ण
		पूर्ण
	पूर्ण
	up_ग_लिखो(&trace_event_sem);
पूर्ण

अटल काष्ठा trace_event_file *
trace_create_new_event(काष्ठा trace_event_call *call,
		       काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_file *file;

	file = kmem_cache_alloc(file_cachep, GFP_TRACE);
	अगर (!file)
		वापस शून्य;

	file->event_call = call;
	file->tr = tr;
	atomic_set(&file->sm_ref, 0);
	atomic_set(&file->पंचांग_ref, 0);
	INIT_LIST_HEAD(&file->triggers);
	list_add(&file->list, &tr->events);

	वापस file;
पूर्ण

/* Add an event to a trace directory */
अटल पूर्णांक
__trace_add_new_event(काष्ठा trace_event_call *call, काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_file *file;

	file = trace_create_new_event(call, tr);
	अगर (!file)
		वापस -ENOMEM;

	अगर (eventdir_initialized)
		वापस event_create_dir(tr->event_dir, file);
	अन्यथा
		वापस event_define_fields(call);
पूर्ण

/*
 * Just create a descriptor क्रम early init. A descriptor is required
 * क्रम enabling events at boot. We want to enable events beक्रमe
 * the fileप्रणाली is initialized.
 */
अटल पूर्णांक
__trace_early_add_new_event(काष्ठा trace_event_call *call,
			    काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_file *file;

	file = trace_create_new_event(call, tr);
	अगर (!file)
		वापस -ENOMEM;

	वापस event_define_fields(call);
पूर्ण

काष्ठा ftrace_module_file_ops;
अटल व्योम __add_event_to_tracers(काष्ठा trace_event_call *call);

/* Add an additional event_call dynamically */
पूर्णांक trace_add_event_call(काष्ठा trace_event_call *call)
अणु
	पूर्णांक ret;
	lockdep_निश्चित_held(&event_mutex);

	mutex_lock(&trace_types_lock);

	ret = __रेजिस्टर_event(call, शून्य);
	अगर (ret >= 0)
		__add_event_to_tracers(call);

	mutex_unlock(&trace_types_lock);
	वापस ret;
पूर्ण

/*
 * Must be called under locking of trace_types_lock, event_mutex and
 * trace_event_sem.
 */
अटल व्योम __trace_हटाओ_event_call(काष्ठा trace_event_call *call)
अणु
	event_हटाओ(call);
	trace_destroy_fields(call);
	मुक्त_event_filter(call->filter);
	call->filter = शून्य;
पूर्ण

अटल पूर्णांक probe_हटाओ_event_call(काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_array *tr;
	काष्ठा trace_event_file *file;

#अगर_घोषित CONFIG_PERF_EVENTS
	अगर (call->perf_refcount)
		वापस -EBUSY;
#पूर्ण_अगर
	करो_क्रम_each_event_file(tr, file) अणु
		अगर (file->event_call != call)
			जारी;
		/*
		 * We can't rely on ftrace_event_enable_disable(enable => 0)
		 * we are going to करो, EVENT_खाता_FL_SOFT_MODE can suppress
		 * TRACE_REG_UNREGISTER.
		 */
		अगर (file->flags & EVENT_खाता_FL_ENABLED)
			वापस -EBUSY;
		/*
		 * The करो_क्रम_each_event_file_safe() is
		 * a द्विगुन loop. After finding the call क्रम this
		 * trace_array, we use अवरोध to jump to the next
		 * trace_array.
		 */
		अवरोध;
	पूर्ण जबतक_क्रम_each_event_file();

	__trace_हटाओ_event_call(call);

	वापस 0;
पूर्ण

/* Remove an event_call */
पूर्णांक trace_हटाओ_event_call(काष्ठा trace_event_call *call)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&event_mutex);

	mutex_lock(&trace_types_lock);
	करोwn_ग_लिखो(&trace_event_sem);
	ret = probe_हटाओ_event_call(call);
	up_ग_लिखो(&trace_event_sem);
	mutex_unlock(&trace_types_lock);

	वापस ret;
पूर्ण

#घोषणा क्रम_each_event(event, start, end)			\
	क्रम (event = start;					\
	     (अचिन्हित दीर्घ)event < (अचिन्हित दीर्घ)end;		\
	     event++)

#अगर_घोषित CONFIG_MODULES

अटल व्योम trace_module_add_events(काष्ठा module *mod)
अणु
	काष्ठा trace_event_call **call, **start, **end;

	अगर (!mod->num_trace_events)
		वापस;

	/* Don't add infraकाष्ठाure क्रम mods without tracepoपूर्णांकs */
	अगर (trace_module_has_bad_taपूर्णांक(mod)) अणु
		pr_err("%s: module has bad taint, not creating trace events\n",
		       mod->name);
		वापस;
	पूर्ण

	start = mod->trace_events;
	end = mod->trace_events + mod->num_trace_events;

	क्रम_each_event(call, start, end) अणु
		__रेजिस्टर_event(*call, mod);
		__add_event_to_tracers(*call);
	पूर्ण
पूर्ण

अटल व्योम trace_module_हटाओ_events(काष्ठा module *mod)
अणु
	काष्ठा trace_event_call *call, *p;

	करोwn_ग_लिखो(&trace_event_sem);
	list_क्रम_each_entry_safe(call, p, &ftrace_events, list) अणु
		अगर (call->mod == mod)
			__trace_हटाओ_event_call(call);
	पूर्ण
	up_ग_लिखो(&trace_event_sem);

	/*
	 * It is safest to reset the ring buffer अगर the module being unloaded
	 * रेजिस्टरed any events that were used. The only worry is अगर
	 * a new module माला_लो loaded, and takes on the same id as the events
	 * of this module. When prपूर्णांकing out the buffer, traced events left
	 * over from this module may be passed to the new module events and
	 * unexpected results may occur.
	 */
	tracing_reset_all_online_cpus();
पूर्ण

अटल पूर्णांक trace_module_notअगरy(काष्ठा notअगरier_block *self,
			       अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा module *mod = data;

	mutex_lock(&event_mutex);
	mutex_lock(&trace_types_lock);
	चयन (val) अणु
	हाल MODULE_STATE_COMING:
		trace_module_add_events(mod);
		अवरोध;
	हाल MODULE_STATE_GOING:
		trace_module_हटाओ_events(mod);
		अवरोध;
	पूर्ण
	mutex_unlock(&trace_types_lock);
	mutex_unlock(&event_mutex);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block trace_module_nb = अणु
	.notअगरier_call = trace_module_notअगरy,
	.priority = 1, /* higher than trace.c module notअगरy */
पूर्ण;
#पूर्ण_अगर /* CONFIG_MODULES */

/* Create a new event directory काष्ठाure क्रम a trace directory. */
अटल व्योम
__trace_add_event_dirs(काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_call *call;
	पूर्णांक ret;

	list_क्रम_each_entry(call, &ftrace_events, list) अणु
		ret = __trace_add_new_event(call, tr);
		अगर (ret < 0)
			pr_warn("Could not create directory for event %s\n",
				trace_event_name(call));
	पूर्ण
पूर्ण

/* Returns any file that matches the प्रणाली and event */
काष्ठा trace_event_file *
__find_event_file(काष्ठा trace_array *tr, स्थिर अक्षर *प्रणाली, स्थिर अक्षर *event)
अणु
	काष्ठा trace_event_file *file;
	काष्ठा trace_event_call *call;
	स्थिर अक्षर *name;

	list_क्रम_each_entry(file, &tr->events, list) अणु

		call = file->event_call;
		name = trace_event_name(call);

		अगर (!name || !call->class)
			जारी;

		अगर (म_भेद(event, name) == 0 &&
		    म_भेद(प्रणाली, call->class->प्रणाली) == 0)
			वापस file;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Returns valid trace event files that match प्रणाली and event */
काष्ठा trace_event_file *
find_event_file(काष्ठा trace_array *tr, स्थिर अक्षर *प्रणाली, स्थिर अक्षर *event)
अणु
	काष्ठा trace_event_file *file;

	file = __find_event_file(tr, प्रणाली, event);
	अगर (!file || !file->event_call->class->reg ||
	    file->event_call->flags & TRACE_EVENT_FL_IGNORE_ENABLE)
		वापस शून्य;

	वापस file;
पूर्ण

/**
 * trace_get_event_file - Find and वापस a trace event file
 * @instance: The name of the trace instance containing the event
 * @प्रणाली: The name of the प्रणाली containing the event
 * @event: The name of the event
 *
 * Return a trace event file given the trace instance name, trace
 * प्रणाली, and trace event name.  If the instance name is शून्य, it
 * refers to the top-level trace array.
 *
 * This function will look it up and वापस it अगर found, after calling
 * trace_array_get() to prevent the instance from going away, and
 * increment the event's module refcount to prevent it from being
 * हटाओd.
 *
 * To release the file, call trace_put_event_file(), which will call
 * trace_array_put() and decrement the event's module refcount.
 *
 * Return: The trace event on success, ERR_PTR otherwise.
 */
काष्ठा trace_event_file *trace_get_event_file(स्थिर अक्षर *instance,
					      स्थिर अक्षर *प्रणाली,
					      स्थिर अक्षर *event)
अणु
	काष्ठा trace_array *tr = top_trace_array();
	काष्ठा trace_event_file *file = शून्य;
	पूर्णांक ret = -EINVAL;

	अगर (instance) अणु
		tr = trace_array_find_get(instance);
		अगर (!tr)
			वापस ERR_PTR(-ENOENT);
	पूर्ण अन्यथा अणु
		ret = trace_array_get(tr);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण

	mutex_lock(&event_mutex);

	file = find_event_file(tr, प्रणाली, event);
	अगर (!file) अणु
		trace_array_put(tr);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Don't let event modules unload जबतक in use */
	ret = try_module_get(file->event_call->mod);
	अगर (!ret) अणु
		trace_array_put(tr);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = 0;
 out:
	mutex_unlock(&event_mutex);

	अगर (ret)
		file = ERR_PTR(ret);

	वापस file;
पूर्ण
EXPORT_SYMBOL_GPL(trace_get_event_file);

/**
 * trace_put_event_file - Release a file from trace_get_event_file()
 * @file: The trace event file
 *
 * If a file was retrieved using trace_get_event_file(), this should
 * be called when it's no दीर्घer needed.  It will cancel the previous
 * trace_array_get() called by that function, and decrement the
 * event's module refcount.
 */
व्योम trace_put_event_file(काष्ठा trace_event_file *file)
अणु
	mutex_lock(&event_mutex);
	module_put(file->event_call->mod);
	mutex_unlock(&event_mutex);

	trace_array_put(file->tr);
पूर्ण
EXPORT_SYMBOL_GPL(trace_put_event_file);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

/* Aव्योम typos */
#घोषणा ENABLE_EVENT_STR	"enable_event"
#घोषणा DISABLE_EVENT_STR	"disable_event"

काष्ठा event_probe_data अणु
	काष्ठा trace_event_file	*file;
	अचिन्हित दीर्घ			count;
	पूर्णांक				ref;
	bool				enable;
पूर्ण;

अटल व्योम update_event_probe(काष्ठा event_probe_data *data)
अणु
	अगर (data->enable)
		clear_bit(EVENT_खाता_FL_SOFT_DISABLED_BIT, &data->file->flags);
	अन्यथा
		set_bit(EVENT_खाता_FL_SOFT_DISABLED_BIT, &data->file->flags);
पूर्ण

अटल व्योम
event_enable_probe(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		   काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
		   व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;
	काष्ठा event_probe_data *edata;
	व्योम **pdata;

	pdata = ftrace_func_mapper_find_ip(mapper, ip);
	अगर (!pdata || !*pdata)
		वापस;

	edata = *pdata;
	update_event_probe(edata);
पूर्ण

अटल व्योम
event_enable_count_probe(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			 काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
			 व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;
	काष्ठा event_probe_data *edata;
	व्योम **pdata;

	pdata = ftrace_func_mapper_find_ip(mapper, ip);
	अगर (!pdata || !*pdata)
		वापस;

	edata = *pdata;

	अगर (!edata->count)
		वापस;

	/* Skip अगर the event is in a state we want to चयन to */
	अगर (edata->enable == !(edata->file->flags & EVENT_खाता_FL_SOFT_DISABLED))
		वापस;

	अगर (edata->count != -1)
		(edata->count)--;

	update_event_probe(edata);
पूर्ण

अटल पूर्णांक
event_enable_prपूर्णांक(काष्ठा seq_file *m, अचिन्हित दीर्घ ip,
		   काष्ठा ftrace_probe_ops *ops, व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;
	काष्ठा event_probe_data *edata;
	व्योम **pdata;

	pdata = ftrace_func_mapper_find_ip(mapper, ip);

	अगर (WARN_ON_ONCE(!pdata || !*pdata))
		वापस 0;

	edata = *pdata;

	seq_म_लिखो(m, "%ps:", (व्योम *)ip);

	seq_म_लिखो(m, "%s:%s:%s",
		   edata->enable ? ENABLE_EVENT_STR : DISABLE_EVENT_STR,
		   edata->file->event_call->class->प्रणाली,
		   trace_event_name(edata->file->event_call));

	अगर (edata->count == -1)
		seq_माला_दो(m, ":unlimited\n");
	अन्यथा
		seq_म_लिखो(m, ":count=%ld\n", edata->count);

	वापस 0;
पूर्ण

अटल पूर्णांक
event_enable_init(काष्ठा ftrace_probe_ops *ops, काष्ठा trace_array *tr,
		  अचिन्हित दीर्घ ip, व्योम *init_data, व्योम **data)
अणु
	काष्ठा ftrace_func_mapper *mapper = *data;
	काष्ठा event_probe_data *edata = init_data;
	पूर्णांक ret;

	अगर (!mapper) अणु
		mapper = allocate_ftrace_func_mapper();
		अगर (!mapper)
			वापस -ENODEV;
		*data = mapper;
	पूर्ण

	ret = ftrace_func_mapper_add_ip(mapper, ip, edata);
	अगर (ret < 0)
		वापस ret;

	edata->ref++;

	वापस 0;
पूर्ण

अटल पूर्णांक मुक्त_probe_data(व्योम *data)
अणु
	काष्ठा event_probe_data *edata = data;

	edata->ref--;
	अगर (!edata->ref) अणु
		/* Remove the SOFT_MODE flag */
		__ftrace_event_enable_disable(edata->file, 0, 1);
		module_put(edata->file->event_call->mod);
		kमुक्त(edata);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
event_enable_मुक्त(काष्ठा ftrace_probe_ops *ops, काष्ठा trace_array *tr,
		  अचिन्हित दीर्घ ip, व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;
	काष्ठा event_probe_data *edata;

	अगर (!ip) अणु
		अगर (!mapper)
			वापस;
		मुक्त_ftrace_func_mapper(mapper, मुक्त_probe_data);
		वापस;
	पूर्ण

	edata = ftrace_func_mapper_हटाओ_ip(mapper, ip);

	अगर (WARN_ON_ONCE(!edata))
		वापस;

	अगर (WARN_ON_ONCE(edata->ref <= 0))
		वापस;

	मुक्त_probe_data(edata);
पूर्ण

अटल काष्ठा ftrace_probe_ops event_enable_probe_ops = अणु
	.func			= event_enable_probe,
	.prपूर्णांक			= event_enable_prपूर्णांक,
	.init			= event_enable_init,
	.मुक्त			= event_enable_मुक्त,
पूर्ण;

अटल काष्ठा ftrace_probe_ops event_enable_count_probe_ops = अणु
	.func			= event_enable_count_probe,
	.prपूर्णांक			= event_enable_prपूर्णांक,
	.init			= event_enable_init,
	.मुक्त			= event_enable_मुक्त,
पूर्ण;

अटल काष्ठा ftrace_probe_ops event_disable_probe_ops = अणु
	.func			= event_enable_probe,
	.prपूर्णांक			= event_enable_prपूर्णांक,
	.init			= event_enable_init,
	.मुक्त			= event_enable_मुक्त,
पूर्ण;

अटल काष्ठा ftrace_probe_ops event_disable_count_probe_ops = अणु
	.func			= event_enable_count_probe,
	.prपूर्णांक			= event_enable_prपूर्णांक,
	.init			= event_enable_init,
	.मुक्त			= event_enable_मुक्त,
पूर्ण;

अटल पूर्णांक
event_enable_func(काष्ठा trace_array *tr, काष्ठा ftrace_hash *hash,
		  अक्षर *glob, अक्षर *cmd, अक्षर *param, पूर्णांक enabled)
अणु
	काष्ठा trace_event_file *file;
	काष्ठा ftrace_probe_ops *ops;
	काष्ठा event_probe_data *data;
	स्थिर अक्षर *प्रणाली;
	स्थिर अक्षर *event;
	अक्षर *number;
	bool enable;
	पूर्णांक ret;

	अगर (!tr)
		वापस -ENODEV;

	/* hash funcs only work with set_ftrace_filter */
	अगर (!enabled || !param)
		वापस -EINVAL;

	प्रणाली = strsep(&param, ":");
	अगर (!param)
		वापस -EINVAL;

	event = strsep(&param, ":");

	mutex_lock(&event_mutex);

	ret = -EINVAL;
	file = find_event_file(tr, प्रणाली, event);
	अगर (!file)
		जाओ out;

	enable = म_भेद(cmd, ENABLE_EVENT_STR) == 0;

	अगर (enable)
		ops = param ? &event_enable_count_probe_ops : &event_enable_probe_ops;
	अन्यथा
		ops = param ? &event_disable_count_probe_ops : &event_disable_probe_ops;

	अगर (glob[0] == '!') अणु
		ret = unरेजिस्टर_ftrace_function_probe_func(glob+1, tr, ops);
		जाओ out;
	पूर्ण

	ret = -ENOMEM;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		जाओ out;

	data->enable = enable;
	data->count = -1;
	data->file = file;

	अगर (!param)
		जाओ out_reg;

	number = strsep(&param, ":");

	ret = -EINVAL;
	अगर (!म_माप(number))
		जाओ out_मुक्त;

	/*
	 * We use the callback data field (which is a poपूर्णांकer)
	 * as our counter.
	 */
	ret = kम_से_अदीर्घ(number, 0, &data->count);
	अगर (ret)
		जाओ out_मुक्त;

 out_reg:
	/* Don't let event modules unload जबतक probe रेजिस्टरed */
	ret = try_module_get(file->event_call->mod);
	अगर (!ret) अणु
		ret = -EBUSY;
		जाओ out_मुक्त;
	पूर्ण

	ret = __ftrace_event_enable_disable(file, 1, 1);
	अगर (ret < 0)
		जाओ out_put;

	ret = रेजिस्टर_ftrace_function_probe(glob, tr, ops, data);
	/*
	 * The above वापसs on success the # of functions enabled,
	 * but अगर it didn't find any functions it वापसs zero.
	 * Consider no functions a failure too.
	 */
	अगर (!ret) अणु
		ret = -ENOENT;
		जाओ out_disable;
	पूर्ण अन्यथा अगर (ret < 0)
		जाओ out_disable;
	/* Just वापस zero, not the number of enabled functions */
	ret = 0;
 out:
	mutex_unlock(&event_mutex);
	वापस ret;

 out_disable:
	__ftrace_event_enable_disable(file, 0, 1);
 out_put:
	module_put(file->event_call->mod);
 out_मुक्त:
	kमुक्त(data);
	जाओ out;
पूर्ण

अटल काष्ठा ftrace_func_command event_enable_cmd = अणु
	.name			= ENABLE_EVENT_STR,
	.func			= event_enable_func,
पूर्ण;

अटल काष्ठा ftrace_func_command event_disable_cmd = अणु
	.name			= DISABLE_EVENT_STR,
	.func			= event_enable_func,
पूर्ण;

अटल __init पूर्णांक रेजिस्टर_event_cmds(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_ftrace_command(&event_enable_cmd);
	अगर (WARN_ON(ret < 0))
		वापस ret;
	ret = रेजिस्टर_ftrace_command(&event_disable_cmd);
	अगर (WARN_ON(ret < 0))
		unरेजिस्टर_ftrace_command(&event_enable_cmd);
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक रेजिस्टर_event_cmds(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

/*
 * The top level array and trace arrays created by boot-समय tracing
 * have alपढ़ोy had its trace_event_file descriptors created in order
 * to allow क्रम early events to be recorded.
 * This function is called after the tracefs has been initialized,
 * and we now have to create the files associated to the events.
 */
अटल व्योम __trace_early_add_event_dirs(काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_file *file;
	पूर्णांक ret;


	list_क्रम_each_entry(file, &tr->events, list) अणु
		ret = event_create_dir(tr->event_dir, file);
		अगर (ret < 0)
			pr_warn("Could not create directory for event %s\n",
				trace_event_name(file->event_call));
	पूर्ण
पूर्ण

/*
 * For early boot up, the top trace array and the trace arrays created
 * by boot-समय tracing require to have a list of events that can be
 * enabled. This must be करोne beक्रमe the fileप्रणाली is set up in order
 * to allow events to be traced early.
 */
व्योम __trace_early_add_events(काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_call *call;
	पूर्णांक ret;

	list_क्रम_each_entry(call, &ftrace_events, list) अणु
		/* Early boot up should not have any modules loaded */
		अगर (WARN_ON_ONCE(call->mod))
			जारी;

		ret = __trace_early_add_new_event(call, tr);
		अगर (ret < 0)
			pr_warn("Could not create early event %s\n",
				trace_event_name(call));
	पूर्ण
पूर्ण

/* Remove the event directory काष्ठाure क्रम a trace directory. */
अटल व्योम
__trace_हटाओ_event_dirs(काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_file *file, *next;

	list_क्रम_each_entry_safe(file, next, &tr->events, list)
		हटाओ_event_file_dir(file);
पूर्ण

अटल व्योम __add_event_to_tracers(काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_array *tr;

	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list)
		__trace_add_new_event(call, tr);
पूर्ण

बाह्य काष्ठा trace_event_call *__start_ftrace_events[];
बाह्य काष्ठा trace_event_call *__stop_ftrace_events[];

अटल अक्षर bootup_event_buf[COMMAND_LINE_SIZE] __initdata;

अटल __init पूर्णांक setup_trace_event(अक्षर *str)
अणु
	strlcpy(bootup_event_buf, str, COMMAND_LINE_SIZE);
	ring_buffer_expanded = true;
	disable_tracing_selftest("running event tracing");

	वापस 1;
पूर्ण
__setup("trace_event=", setup_trace_event);

/* Expects to have event_mutex held when called */
अटल पूर्णांक
create_event_toplevel_files(काष्ठा dentry *parent, काष्ठा trace_array *tr)
अणु
	काष्ठा dentry *d_events;
	काष्ठा dentry *entry;

	entry = tracefs_create_file("set_event", 0644, parent,
				    tr, &ftrace_set_event_fops);
	अगर (!entry) अणु
		pr_warn("Could not create tracefs 'set_event' entry\n");
		वापस -ENOMEM;
	पूर्ण

	d_events = tracefs_create_dir("events", parent);
	अगर (!d_events) अणु
		pr_warn("Could not create tracefs 'events' directory\n");
		वापस -ENOMEM;
	पूर्ण

	entry = trace_create_file("enable", 0644, d_events,
				  tr, &ftrace_tr_enable_fops);
	अगर (!entry) अणु
		pr_warn("Could not create tracefs 'enable' entry\n");
		वापस -ENOMEM;
	पूर्ण

	/* There are not as crucial, just warn अगर they are not created */

	entry = tracefs_create_file("set_event_pid", 0644, parent,
				    tr, &ftrace_set_event_pid_fops);
	अगर (!entry)
		pr_warn("Could not create tracefs 'set_event_pid' entry\n");

	entry = tracefs_create_file("set_event_notrace_pid", 0644, parent,
				    tr, &ftrace_set_event_notrace_pid_fops);
	अगर (!entry)
		pr_warn("Could not create tracefs 'set_event_notrace_pid' entry\n");

	/* ring buffer पूर्णांकernal क्रमmats */
	entry = trace_create_file("header_page", 0444, d_events,
				  ring_buffer_prपूर्णांक_page_header,
				  &ftrace_show_header_fops);
	अगर (!entry)
		pr_warn("Could not create tracefs 'header_page' entry\n");

	entry = trace_create_file("header_event", 0444, d_events,
				  ring_buffer_prपूर्णांक_entry_header,
				  &ftrace_show_header_fops);
	अगर (!entry)
		pr_warn("Could not create tracefs 'header_event' entry\n");

	tr->event_dir = d_events;

	वापस 0;
पूर्ण

/**
 * event_trace_add_tracer - add a instance of a trace_array to events
 * @parent: The parent dentry to place the files/directories क्रम events in
 * @tr: The trace array associated with these events
 *
 * When a new instance is created, it needs to set up its events
 * directory, as well as other files associated with events. It also
 * creates the event hierarchy in the @parent/events directory.
 *
 * Returns 0 on success.
 *
 * Must be called with event_mutex held.
 */
पूर्णांक event_trace_add_tracer(काष्ठा dentry *parent, काष्ठा trace_array *tr)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&event_mutex);

	ret = create_event_toplevel_files(parent, tr);
	अगर (ret)
		जाओ out;

	करोwn_ग_लिखो(&trace_event_sem);
	/* If tr alपढ़ोy has the event list, it is initialized in early boot. */
	अगर (unlikely(!list_empty(&tr->events)))
		__trace_early_add_event_dirs(tr);
	अन्यथा
		__trace_add_event_dirs(tr);
	up_ग_लिखो(&trace_event_sem);

 out:
	वापस ret;
पूर्ण

/*
 * The top trace array alपढ़ोy had its file descriptors created.
 * Now the files themselves need to be created.
 */
अटल __init पूर्णांक
early_event_add_tracer(काष्ठा dentry *parent, काष्ठा trace_array *tr)
अणु
	पूर्णांक ret;

	mutex_lock(&event_mutex);

	ret = create_event_toplevel_files(parent, tr);
	अगर (ret)
		जाओ out_unlock;

	करोwn_ग_लिखो(&trace_event_sem);
	__trace_early_add_event_dirs(tr);
	up_ग_लिखो(&trace_event_sem);

 out_unlock:
	mutex_unlock(&event_mutex);

	वापस ret;
पूर्ण

/* Must be called with event_mutex held */
पूर्णांक event_trace_del_tracer(काष्ठा trace_array *tr)
अणु
	lockdep_निश्चित_held(&event_mutex);

	/* Disable any event triggers and associated soft-disabled events */
	clear_event_triggers(tr);

	/* Clear the pid list */
	__ftrace_clear_event_pids(tr, TRACE_PIDS | TRACE_NO_PIDS);

	/* Disable any running events */
	__ftrace_set_clr_event_nolock(tr, शून्य, शून्य, शून्य, 0);

	/* Make sure no more events are being executed */
	tracepoपूर्णांक_synchronize_unरेजिस्टर();

	करोwn_ग_लिखो(&trace_event_sem);
	__trace_हटाओ_event_dirs(tr);
	tracefs_हटाओ(tr->event_dir);
	up_ग_लिखो(&trace_event_sem);

	tr->event_dir = शून्य;

	वापस 0;
पूर्ण

अटल __init पूर्णांक event_trace_स_रखोup(व्योम)
अणु
	field_cachep = KMEM_CACHE(ftrace_event_field, SLAB_PANIC);
	file_cachep = KMEM_CACHE(trace_event_file, SLAB_PANIC);
	वापस 0;
पूर्ण

अटल __init व्योम
early_enable_events(काष्ठा trace_array *tr, bool disable_first)
अणु
	अक्षर *buf = bootup_event_buf;
	अक्षर *token;
	पूर्णांक ret;

	जबतक (true) अणु
		token = strsep(&buf, ",");

		अगर (!token)
			अवरोध;

		अगर (*token) अणु
			/* Restarting syscalls requires that we stop them first */
			अगर (disable_first)
				ftrace_set_clr_event(tr, token, 0);

			ret = ftrace_set_clr_event(tr, token, 1);
			अगर (ret)
				pr_warn("Failed to enable trace event: %s\n", token);
		पूर्ण

		/* Put back the comma to allow this to be called again */
		अगर (buf)
			*(buf - 1) = ',';
	पूर्ण
पूर्ण

अटल __init पूर्णांक event_trace_enable(व्योम)
अणु
	काष्ठा trace_array *tr = top_trace_array();
	काष्ठा trace_event_call **iter, *call;
	पूर्णांक ret;

	अगर (!tr)
		वापस -ENODEV;

	क्रम_each_event(iter, __start_ftrace_events, __stop_ftrace_events) अणु

		call = *iter;
		ret = event_init(call);
		अगर (!ret)
			list_add(&call->list, &ftrace_events);
	पूर्ण

	/*
	 * We need the top trace array to have a working set of trace
	 * poपूर्णांकs at early init, beक्रमe the debug files and directories
	 * are created. Create the file entries now, and attach them
	 * to the actual file dentries later.
	 */
	__trace_early_add_events(tr);

	early_enable_events(tr, false);

	trace_prपूर्णांकk_start_comm();

	रेजिस्टर_event_cmds();

	रेजिस्टर_trigger_cmds();

	वापस 0;
पूर्ण

/*
 * event_trace_enable() is called from trace_event_init() first to
 * initialize events and perhaps start any events that are on the
 * command line. Unक्रमtunately, there are some events that will not
 * start this early, like the प्रणाली call tracepoपूर्णांकs that need
 * to set the %SYSCALL_WORK_SYSCALL_TRACEPOINT flag of pid 1. But
 * event_trace_enable() is called beक्रमe pid 1 starts, and this flag
 * is never set, making the syscall tracepoपूर्णांक never get reached, but
 * the event is enabled regardless (and not करोing anything).
 */
अटल __init पूर्णांक event_trace_enable_again(व्योम)
अणु
	काष्ठा trace_array *tr;

	tr = top_trace_array();
	अगर (!tr)
		वापस -ENODEV;

	early_enable_events(tr, true);

	वापस 0;
पूर्ण

early_initcall(event_trace_enable_again);

/* Init fields which करोesn't related to the tracefs */
अटल __init पूर्णांक event_trace_init_fields(व्योम)
अणु
	अगर (trace_define_generic_fields())
		pr_warn("tracing: Failed to allocated generic fields");

	अगर (trace_define_common_fields())
		pr_warn("tracing: Failed to allocate common fields");

	वापस 0;
पूर्ण

__init पूर्णांक event_trace_init(व्योम)
अणु
	काष्ठा trace_array *tr;
	काष्ठा dentry *entry;
	पूर्णांक ret;

	tr = top_trace_array();
	अगर (!tr)
		वापस -ENODEV;

	entry = tracefs_create_file("available_events", 0444, शून्य,
				    tr, &ftrace_avail_fops);
	अगर (!entry)
		pr_warn("Could not create tracefs 'available_events' entry\n");

	ret = early_event_add_tracer(शून्य, tr);
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_MODULES
	ret = रेजिस्टर_module_notअगरier(&trace_module_nb);
	अगर (ret)
		pr_warn("Failed to register trace events module notifier\n");
#पूर्ण_अगर

	eventdir_initialized = true;

	वापस 0;
पूर्ण

व्योम __init trace_event_init(व्योम)
अणु
	event_trace_स_रखोup();
	init_ftrace_syscalls();
	event_trace_enable();
	event_trace_init_fields();
पूर्ण

#अगर_घोषित CONFIG_EVENT_TRACE_STARTUP_TEST

अटल DEFINE_SPINLOCK(test_spinlock);
अटल DEFINE_SPINLOCK(test_spinlock_irq);
अटल DEFINE_MUTEX(test_mutex);

अटल __init व्योम test_work(काष्ठा work_काष्ठा *dummy)
अणु
	spin_lock(&test_spinlock);
	spin_lock_irq(&test_spinlock_irq);
	udelay(1);
	spin_unlock_irq(&test_spinlock_irq);
	spin_unlock(&test_spinlock);

	mutex_lock(&test_mutex);
	msleep(1);
	mutex_unlock(&test_mutex);
पूर्ण

अटल __init पूर्णांक event_test_thपढ़ो(व्योम *unused)
अणु
	व्योम *test_दो_स्मृति;

	test_दो_स्मृति = kदो_स्मृति(1234, GFP_KERNEL);
	अगर (!test_दो_स्मृति)
		pr_info("failed to kmalloc\n");

	schedule_on_each_cpu(test_work);

	kमुक्त(test_दो_स्मृति);

	set_current_state(TASK_INTERRUPTIBLE);
	जबतक (!kthपढ़ो_should_stop()) अणु
		schedule();
		set_current_state(TASK_INTERRUPTIBLE);
	पूर्ण
	__set_current_state(TASK_RUNNING);

	वापस 0;
पूर्ण

/*
 * Do various things that may trigger events.
 */
अटल __init व्योम event_test_stuff(व्योम)
अणु
	काष्ठा task_काष्ठा *test_thपढ़ो;

	test_thपढ़ो = kthपढ़ो_run(event_test_thपढ़ो, शून्य, "test-events");
	msleep(1);
	kthपढ़ो_stop(test_thपढ़ो);
पूर्ण

/*
 * For every trace event defined, we will test each trace poपूर्णांक separately,
 * and then by groups, and finally all trace poपूर्णांकs.
 */
अटल __init व्योम event_trace_self_tests(व्योम)
अणु
	काष्ठा trace_subप्रणाली_dir *dir;
	काष्ठा trace_event_file *file;
	काष्ठा trace_event_call *call;
	काष्ठा event_subप्रणाली *प्रणाली;
	काष्ठा trace_array *tr;
	पूर्णांक ret;

	tr = top_trace_array();
	अगर (!tr)
		वापस;

	pr_info("Running tests on trace events:\n");

	list_क्रम_each_entry(file, &tr->events, list) अणु

		call = file->event_call;

		/* Only test those that have a probe */
		अगर (!call->class || !call->class->probe)
			जारी;

/*
 * Testing syscall events here is pretty useless, but
 * we still करो it अगर configured. But this is समय consuming.
 * What we really need is a user thपढ़ो to perक्रमm the
 * syscalls as we test.
 */
#अगर_अघोषित CONFIG_EVENT_TRACE_TEST_SYSCALLS
		अगर (call->class->प्रणाली &&
		    म_भेद(call->class->प्रणाली, "syscalls") == 0)
			जारी;
#पूर्ण_अगर

		pr_info("Testing event %s: ", trace_event_name(call));

		/*
		 * If an event is alपढ़ोy enabled, someone is using
		 * it and the self test should not be on.
		 */
		अगर (file->flags & EVENT_खाता_FL_ENABLED) अणु
			pr_warn("Enabled event during self test!\n");
			WARN_ON_ONCE(1);
			जारी;
		पूर्ण

		ftrace_event_enable_disable(file, 1);
		event_test_stuff();
		ftrace_event_enable_disable(file, 0);

		pr_cont("OK\n");
	पूर्ण

	/* Now test at the sub प्रणाली level */

	pr_info("Running tests on trace event systems:\n");

	list_क्रम_each_entry(dir, &tr->प्रणालीs, list) अणु

		प्रणाली = dir->subप्रणाली;

		/* the ftrace प्रणाली is special, skip it */
		अगर (म_भेद(प्रणाली->name, "ftrace") == 0)
			जारी;

		pr_info("Testing event system %s: ", प्रणाली->name);

		ret = __ftrace_set_clr_event(tr, शून्य, प्रणाली->name, शून्य, 1);
		अगर (WARN_ON_ONCE(ret)) अणु
			pr_warn("error enabling system %s\n",
				प्रणाली->name);
			जारी;
		पूर्ण

		event_test_stuff();

		ret = __ftrace_set_clr_event(tr, शून्य, प्रणाली->name, शून्य, 0);
		अगर (WARN_ON_ONCE(ret)) अणु
			pr_warn("error disabling system %s\n",
				प्रणाली->name);
			जारी;
		पूर्ण

		pr_cont("OK\n");
	पूर्ण

	/* Test with all events enabled */

	pr_info("Running tests on all trace events:\n");
	pr_info("Testing all events: ");

	ret = __ftrace_set_clr_event(tr, शून्य, शून्य, शून्य, 1);
	अगर (WARN_ON_ONCE(ret)) अणु
		pr_warn("error enabling all events\n");
		वापस;
	पूर्ण

	event_test_stuff();

	/* reset sysname */
	ret = __ftrace_set_clr_event(tr, शून्य, शून्य, शून्य, 0);
	अगर (WARN_ON_ONCE(ret)) अणु
		pr_warn("error disabling all events\n");
		वापस;
	पूर्ण

	pr_cont("OK\n");
पूर्ण

#अगर_घोषित CONFIG_FUNCTION_TRACER

अटल DEFINE_PER_CPU(atomic_t, ftrace_test_event_disable);

अटल काष्ठा trace_event_file event_trace_file __initdata;

अटल व्योम __init
function_test_events_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			  काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *regs)
अणु
	काष्ठा trace_buffer *buffer;
	काष्ठा ring_buffer_event *event;
	काष्ठा ftrace_entry *entry;
	अचिन्हित पूर्णांक trace_ctx;
	दीर्घ disabled;
	पूर्णांक cpu;

	trace_ctx = tracing_gen_ctx();
	preempt_disable_notrace();
	cpu = raw_smp_processor_id();
	disabled = atomic_inc_वापस(&per_cpu(ftrace_test_event_disable, cpu));

	अगर (disabled != 1)
		जाओ out;

	event = trace_event_buffer_lock_reserve(&buffer, &event_trace_file,
						TRACE_FN, माप(*entry),
						trace_ctx);
	अगर (!event)
		जाओ out;
	entry	= ring_buffer_event_data(event);
	entry->ip			= ip;
	entry->parent_ip		= parent_ip;

	event_trigger_unlock_commit(&event_trace_file, buffer, event,
				    entry, trace_ctx);
 out:
	atomic_dec(&per_cpu(ftrace_test_event_disable, cpu));
	preempt_enable_notrace();
पूर्ण

अटल काष्ठा ftrace_ops trace_ops __initdata  =
अणु
	.func = function_test_events_call,
पूर्ण;

अटल __init व्योम event_trace_self_test_with_function(व्योम)
अणु
	पूर्णांक ret;

	event_trace_file.tr = top_trace_array();
	अगर (WARN_ON(!event_trace_file.tr))
		वापस;

	ret = रेजिस्टर_ftrace_function(&trace_ops);
	अगर (WARN_ON(ret < 0)) अणु
		pr_info("Failed to enable function tracer for event tests\n");
		वापस;
	पूर्ण
	pr_info("Running tests again, along with the function tracer\n");
	event_trace_self_tests();
	unरेजिस्टर_ftrace_function(&trace_ops);
पूर्ण
#अन्यथा
अटल __init व्योम event_trace_self_test_with_function(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल __init पूर्णांक event_trace_self_tests_init(व्योम)
अणु
	अगर (!tracing_selftest_disabled) अणु
		event_trace_self_tests();
		event_trace_self_test_with_function();
	पूर्ण

	वापस 0;
पूर्ण

late_initcall(event_trace_self_tests_init);

#पूर्ण_अगर
