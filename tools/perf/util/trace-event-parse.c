<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009, Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>

#समावेश "debug.h"
#समावेश "trace-event.h"

#समावेश <linux/प्रकार.स>

अटल पूर्णांक get_common_field(काष्ठा scripting_context *context,
			    पूर्णांक *offset, पूर्णांक *size, स्थिर अक्षर *type)
अणु
	काष्ठा tep_handle *pevent = context->pevent;
	काष्ठा tep_event *event;
	काष्ठा tep_क्रमmat_field *field;

	अगर (!*size) अणु

		event = tep_get_first_event(pevent);
		अगर (!event)
			वापस 0;

		field = tep_find_common_field(event, type);
		अगर (!field)
			वापस 0;
		*offset = field->offset;
		*size = field->size;
	पूर्ण

	वापस tep_पढ़ो_number(pevent, context->event_data + *offset, *size);
पूर्ण

पूर्णांक common_lock_depth(काष्ठा scripting_context *context)
अणु
	अटल पूर्णांक offset;
	अटल पूर्णांक size;
	पूर्णांक ret;

	ret = get_common_field(context, &size, &offset,
			       "common_lock_depth");
	अगर (ret < 0)
		वापस -1;

	वापस ret;
पूर्ण

पूर्णांक common_flags(काष्ठा scripting_context *context)
अणु
	अटल पूर्णांक offset;
	अटल पूर्णांक size;
	पूर्णांक ret;

	ret = get_common_field(context, &size, &offset,
			       "common_flags");
	अगर (ret < 0)
		वापस -1;

	वापस ret;
पूर्ण

पूर्णांक common_pc(काष्ठा scripting_context *context)
अणु
	अटल पूर्णांक offset;
	अटल पूर्णांक size;
	पूर्णांक ret;

	ret = get_common_field(context, &size, &offset,
			       "common_preempt_count");
	अगर (ret < 0)
		वापस -1;

	वापस ret;
पूर्ण

अचिन्हित दीर्घ दीर्घ
raw_field_value(काष्ठा tep_event *event, स्थिर अक्षर *name, व्योम *data)
अणु
	काष्ठा tep_क्रमmat_field *field;
	अचिन्हित दीर्घ दीर्घ val;

	field = tep_find_any_field(event, name);
	अगर (!field)
		वापस 0ULL;

	tep_पढ़ो_number_field(field, data, &val);

	वापस val;
पूर्ण

अचिन्हित दीर्घ दीर्घ पढ़ो_size(काष्ठा tep_event *event, व्योम *ptr, पूर्णांक size)
अणु
	वापस tep_पढ़ो_number(event->tep, ptr, size);
पूर्ण

व्योम event_क्रमmat__ख_लिखो(काष्ठा tep_event *event,
			   पूर्णांक cpu, व्योम *data, पूर्णांक size, खाता *fp)
अणु
	काष्ठा tep_record record;
	काष्ठा trace_seq s;

	स_रखो(&record, 0, माप(record));
	record.cpu = cpu;
	record.size = size;
	record.data = data;

	trace_seq_init(&s);
	tep_prपूर्णांक_event(event->tep, &s, &record, "%s", TEP_PRINT_INFO);
	trace_seq_करो_ख_लिखो(&s, fp);
	trace_seq_destroy(&s);
पूर्ण

व्योम event_क्रमmat__prपूर्णांक(काष्ठा tep_event *event,
			 पूर्णांक cpu, व्योम *data, पूर्णांक size)
अणु
	वापस event_क्रमmat__ख_लिखो(event, cpu, data, size, मानक_निकास);
पूर्ण

व्योम parse_ftrace_prपूर्णांकk(काष्ठा tep_handle *pevent,
			 अक्षर *file, अचिन्हित पूर्णांक size __maybe_unused)
अणु
	अचिन्हित दीर्घ दीर्घ addr;
	अक्षर *prपूर्णांकk;
	अक्षर *line;
	अक्षर *next = शून्य;
	अक्षर *addr_str;
	अक्षर *fmt = शून्य;

	line = म_मोहर_r(file, "\n", &next);
	जबतक (line) अणु
		addr_str = म_मोहर_r(line, ":", &fmt);
		अगर (!addr_str) अणु
			pr_warning("printk format with empty entry");
			अवरोध;
		पूर्ण
		addr = म_से_अदीर्घl(addr_str, शून्य, 16);
		/* fmt still has a space, skip it */
		prपूर्णांकk = strdup(fmt+1);
		line = म_मोहर_r(शून्य, "\n", &next);
		tep_रेजिस्टर_prपूर्णांक_string(pevent, prपूर्णांकk, addr);
		मुक्त(prपूर्णांकk);
	पूर्ण
पूर्ण

व्योम parse_saved_cmdline(काष्ठा tep_handle *pevent,
			 अक्षर *file, अचिन्हित पूर्णांक size __maybe_unused)
अणु
	अक्षर comm[17]; /* Max comm length in the kernel is 16. */
	अक्षर *line;
	अक्षर *next = शून्य;
	पूर्णांक pid;

	line = म_मोहर_r(file, "\n", &next);
	जबतक (line) अणु
		अगर (माला_पूछो(line, "%d %16s", &pid, comm) == 2)
			tep_रेजिस्टर_comm(pevent, comm, pid);
		line = म_मोहर_r(शून्य, "\n", &next);
	पूर्ण
पूर्ण

पूर्णांक parse_ftrace_file(काष्ठा tep_handle *pevent, अक्षर *buf, अचिन्हित दीर्घ size)
अणु
	वापस tep_parse_event(pevent, buf, size, "ftrace");
पूर्ण

पूर्णांक parse_event_file(काष्ठा tep_handle *pevent,
		     अक्षर *buf, अचिन्हित दीर्घ size, अक्षर *sys)
अणु
	वापस tep_parse_event(pevent, buf, size, sys);
पूर्ण

काष्ठा flag अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ दीर्घ value;
पूर्ण;

अटल स्थिर काष्ठा flag flags[] = अणु
	अणु "HI_SOFTIRQ", 0 पूर्ण,
	अणु "TIMER_SOFTIRQ", 1 पूर्ण,
	अणु "NET_TX_SOFTIRQ", 2 पूर्ण,
	अणु "NET_RX_SOFTIRQ", 3 पूर्ण,
	अणु "BLOCK_SOFTIRQ", 4 पूर्ण,
	अणु "IRQ_POLL_SOFTIRQ", 5 पूर्ण,
	अणु "TASKLET_SOFTIRQ", 6 पूर्ण,
	अणु "SCHED_SOFTIRQ", 7 पूर्ण,
	अणु "HRTIMER_SOFTIRQ", 8 पूर्ण,
	अणु "RCU_SOFTIRQ", 9 पूर्ण,

	अणु "HRTIMER_NORESTART", 0 पूर्ण,
	अणु "HRTIMER_RESTART", 1 पूर्ण,
पूर्ण;

अचिन्हित दीर्घ दीर्घ eval_flag(स्थिर अक्षर *flag)
अणु
	पूर्णांक i;

	/*
	 * Some flags in the क्रमmat files करो not get converted.
	 * If the flag is not numeric, see अगर it is something that
	 * we alपढ़ोy know about.
	 */
	अगर (है_अंक(flag[0]))
		वापस म_से_अदीर्घl(flag, शून्य, 0);

	क्रम (i = 0; i < (पूर्णांक)(माप(flags)/माप(flags[0])); i++)
		अगर (म_भेद(flags[i].name, flag) == 0)
			वापस flags[i].value;

	वापस 0;
पूर्ण
