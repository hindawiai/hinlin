<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 * Copyright (C) 2009 Johannes Berg <johannes@sipsolutions.net>
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "event-parse.h"
#समावेश "trace-seq.h"

अटल पूर्णांक समयr_expire_handler(काष्ठा trace_seq *s,
				काष्ठा tep_record *record,
				काष्ठा tep_event *event, व्योम *context)
अणु
	trace_seq_म_लिखो(s, "hrtimer=");

	अगर (tep_prपूर्णांक_num_field(s, "0x%llx", event, "timer",
				record, 0) == -1)
		tep_prपूर्णांक_num_field(s, "0x%llx", event, "hrtimer",
				    record, 1);

	trace_seq_म_लिखो(s, " now=");

	tep_prपूर्णांक_num_field(s, "%llu", event, "now", record, 1);

	tep_prपूर्णांक_func_field(s, " function=%s", event, "function",
				record, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक समयr_start_handler(काष्ठा trace_seq *s,
			       काष्ठा tep_record *record,
			       काष्ठा tep_event *event, व्योम *context)
अणु
	trace_seq_म_लिखो(s, "hrtimer=");

	अगर (tep_prपूर्णांक_num_field(s, "0x%llx", event, "timer",
				record, 0) == -1)
		tep_prपूर्णांक_num_field(s, "0x%llx", event, "hrtimer",
				    record, 1);

	tep_prपूर्णांक_func_field(s, " function=%s", event, "function",
			     record, 0);

	trace_seq_म_लिखो(s, " expires=");
	tep_prपूर्णांक_num_field(s, "%llu", event, "expires", record, 1);

	trace_seq_म_लिखो(s, " softexpires=");
	tep_prपूर्णांक_num_field(s, "%llu", event, "softexpires", record, 1);
	वापस 0;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	tep_रेजिस्टर_event_handler(tep, -1,
				   "timer", "hrtimer_expire_entry",
				   समयr_expire_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "timer", "hrtimer_start",
				   समयr_start_handler, शून्य);
	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	tep_unरेजिस्टर_event_handler(tep, -1,
				     "timer", "hrtimer_expire_entry",
				     समयr_expire_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "timer", "hrtimer_start",
				     समयr_start_handler, शून्य);
पूर्ण
