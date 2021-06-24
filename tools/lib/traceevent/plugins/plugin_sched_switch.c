<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009, 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "event-parse.h"
#समावेश "trace-seq.h"

अटल व्योम ग_लिखो_state(काष्ठा trace_seq *s, पूर्णांक val)
अणु
	स्थिर अक्षर states[] = "SDTtZXxW";
	पूर्णांक found = 0;
	पूर्णांक i;

	क्रम (i = 0; i < (माप(states) - 1); i++) अणु
		अगर (!(val & (1 << i)))
			जारी;

		अगर (found)
			trace_seq_अ_दो(s, '|');

		found = 1;
		trace_seq_अ_दो(s, states[i]);
	पूर्ण

	अगर (!found)
		trace_seq_अ_दो(s, 'R');
पूर्ण

अटल व्योम ग_लिखो_and_save_comm(काष्ठा tep_क्रमmat_field *field,
				काष्ठा tep_record *record,
				काष्ठा trace_seq *s, पूर्णांक pid)
अणु
	स्थिर अक्षर *comm;
	पूर्णांक len;

	comm = (अक्षर *)(record->data + field->offset);
	len = s->len;
	trace_seq_म_लिखो(s, "%.*s",
			 field->size, comm);

	/* make sure the comm has a \0 at the end. */
	trace_seq_terminate(s);
	comm = &s->buffer[len];

	/* Help out the comm to ids. This will handle dups */
	tep_रेजिस्टर_comm(field->event->tep, comm, pid);
पूर्ण

अटल पूर्णांक sched_wakeup_handler(काष्ठा trace_seq *s,
				काष्ठा tep_record *record,
				काष्ठा tep_event *event, व्योम *context)
अणु
	काष्ठा tep_क्रमmat_field *field;
	अचिन्हित दीर्घ दीर्घ val;

	अगर (tep_get_field_val(s, event, "pid", record, &val, 1))
		वापस trace_seq_अ_दो(s, '!');

	field = tep_find_any_field(event, "comm");
	अगर (field) अणु
		ग_लिखो_and_save_comm(field, record, s, val);
		trace_seq_अ_दो(s, ':');
	पूर्ण
	trace_seq_म_लिखो(s, "%lld", val);

	अगर (tep_get_field_val(s, event, "prio", record, &val, 0) == 0)
		trace_seq_म_लिखो(s, " [%lld]", val);

	अगर (tep_get_field_val(s, event, "success", record, &val, 1) == 0)
		trace_seq_म_लिखो(s, " success=%lld", val);

	अगर (tep_get_field_val(s, event, "target_cpu", record, &val, 0) == 0)
		trace_seq_म_लिखो(s, " CPU:%03llu", val);

	वापस 0;
पूर्ण

अटल पूर्णांक sched_चयन_handler(काष्ठा trace_seq *s,
				काष्ठा tep_record *record,
				काष्ठा tep_event *event, व्योम *context)
अणु
	काष्ठा tep_क्रमmat_field *field;
	अचिन्हित दीर्घ दीर्घ val;

	अगर (tep_get_field_val(s, event, "prev_pid", record, &val, 1))
		वापस trace_seq_अ_दो(s, '!');

	field = tep_find_any_field(event, "prev_comm");
	अगर (field) अणु
		ग_लिखो_and_save_comm(field, record, s, val);
		trace_seq_अ_दो(s, ':');
	पूर्ण
	trace_seq_म_लिखो(s, "%lld ", val);

	अगर (tep_get_field_val(s, event, "prev_prio", record, &val, 0) == 0)
		trace_seq_म_लिखो(s, "[%d] ", (पूर्णांक) val);

	अगर (tep_get_field_val(s,  event, "prev_state", record, &val, 0) == 0)
		ग_लिखो_state(s, val);

	trace_seq_माला_दो(s, " ==> ");

	अगर (tep_get_field_val(s, event, "next_pid", record, &val, 1))
		वापस trace_seq_अ_दो(s, '!');

	field = tep_find_any_field(event, "next_comm");
	अगर (field) अणु
		ग_लिखो_and_save_comm(field, record, s, val);
		trace_seq_अ_दो(s, ':');
	पूर्ण
	trace_seq_म_लिखो(s, "%lld", val);

	अगर (tep_get_field_val(s, event, "next_prio", record, &val, 0) == 0)
		trace_seq_म_लिखो(s, " [%d]", (पूर्णांक) val);

	वापस 0;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	tep_रेजिस्टर_event_handler(tep, -1, "sched", "sched_switch",
				   sched_चयन_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "sched", "sched_wakeup",
				   sched_wakeup_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "sched", "sched_wakeup_new",
				   sched_wakeup_handler, शून्य);
	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	tep_unरेजिस्टर_event_handler(tep, -1, "sched", "sched_switch",
				     sched_चयन_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "sched", "sched_wakeup",
				     sched_wakeup_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "sched", "sched_wakeup_new",
				     sched_wakeup_handler, शून्य);
पूर्ण
